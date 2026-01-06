(* game.sml

   Miguel Villanueva
   CS 210            
 ----------------------------------------------------------------------
 {SOURCES CONSULTED}
 http://www2.cs.uidaho.edu/~jeffery/courses/210/lecture.html#lecture19
 http://www2.cs.uidaho.edu/~jeffery/courses/210/lecture.html#lecture24
 https://learnxinyminutes.com/docs/standard-ml/
 https://stackoverflow.com/questions/22067535/generating-a-random-
         number-in-sml
 https://www.smlnj.org/doc/interact.html
 https://stackoverflow.com/questions/818324/loops-in-sml-nj
 https://stackoverflow.com/questions/43075607/how-to-get-an-integer-
         as-user-input-in-sml
 http://sml-family.org/Basis/text-io.html
 http://rigaux.org/language-study/syntax-across-languages-per-
        language/SML.html
 https://stackoverflow.com/questions/7548139/sml-nj-while-loop
 https://stackoverflow.com/questions/19529612/what-does-val-it-unit-
         mean-in-sml
 https://stackoverflow.com/questions/28510700/how-to-print-variable-
         in-sml
 https://stackoverflow.com/questions/14445927/syntax-of-nested-if-
         else-in-sml
 https://stackoverflow.com/questions/9056624/elseif-statement-in-
         standard-ml
 https://stackoverflow.com/questions/2696276/sml-nj-getting-user-input
 https://www.cs.cornell.edu/courses/cs312/2004fa/lectures/rec21.html
 https://stackoverflow.com/questions/42148055/sml-how-to-append-an-
         element-to-a-list-in-sml
 https://stackoverflow.com/questions/18291683/remove-elements-from-a-
         list-in-ml/18291804
 https://courses.cs.washington.edu/courses/cse341/04wi/lectures/08-
         ml-refs.html
 https://stackoverflow.com/questions/18291683/remove-elements-from-a-
         list-in-ml/18291804
 https://stackoverflow.com/questions/48691160/sml-error-unresolved-
         flex-record
 http://smlfamily.github.io/Basis/bool.html
 https://stackoverflow.com/questions/15229778/how-can-i-use-if-
         statement-in-let-statement
 ----------------------------------------------------------------------
 ---------------------------------------------------------------------- *)
    
val health = ref 30;
val aiHealth = ref 30;
val userHand = ref [ (5, false, "trombone", 13, 7),
                     (5, false, "trumpet", 18, 2),
                     (4, false, "tuba", 2, 13),
                     (4, false, "flugelhorn", 12, 3),
                     (4, true, "snare drum", 9, 0),
                     (3, true, "bass drum", 7, 0),
                     (3, false, "french horn", 6, 4),
                     (3, false, "cornet", 8, 2),
                     (2, false, "mellophone", 6, 1),
                     (2, false, "euphonium", 2, 5),
                     (2, false, "sackbut", 4, 3),
                     (2, true, "tambourine", 5, 0), 
	             (1, true, "triangle", 3, 0),
                     (1, false, "baritone", 1, 3),
                     (1, false, "bugle", 2, 2),
                     (1, false, "alto trombone", 3, 1),
                     (1, false, "pocket trumpet", 3, 1) 
                   ];

val aiHand = ref [ (5, false, "bagpipes", 5, 15),
                   (5, false, "ocarina", 14, 6),
                   (4, false, "bassoon", 3, 12),
                   (4, false, "native american flute", 11, 4), 
	           (4, true, "guitar", 9, 0),
                   (3, true, "cello", 7, 0),
                   (3, false, "saxophone", 9, 1),
                   (3, false, "slide whistle", 5, 5),
                   (2, false, "flute", 6, 1),
                   (2, false, "oboe", 1, 6),
                   (2, false, "clarinet", 2, 5),
                   (2, true, "erhu", 5, 0),
                   (1, true, "banjo", 3, 0), 
                   (1, false, "recorder", 1, 3),
                   (1, false, "piccolo", 3, 1),
                   (1, false, "fife", 2, 2),
                   (1, false, "panflute", 1, 3)	 
                 ];
val minions = ref []:(string*int*int)list ref;
val monsters = ref []:(string*int*int)list ref;

val justPlayedU = ref []:(string*int*int)list ref;

(*  ======= {GET FUNCTIONS} ======= 
      used to get specific element
            for cards in hand 
    ===============================  *)   
fun getCost (card:(int*bool*string*int*int)) =
  #1(card);
fun getSpell (card:(int*bool*string*int*int)) =
  #2(card);
fun getName (card:(int*bool*string*int*int)) =
  #3(card);
fun getAttack (card:(int*bool*string*int*int)) =
  #4(card);
fun getHealth (card:(int*bool*string*int*int)) =
  #5(card);

(* ======= {PRINT GIVEN HAND} ======= 
       takes either ai or user hand
           and prints elements
   ==================================  *)
fun printHand (list:(int*bool*string*int*int)list) =
  if null list then nil
  else
    let 
      val card = hd(list)
      val spell = getSpell(card)
      val name = getName(card)
      val cost = getCost(card)
      val attack = getAttack(card)
      val health = getHealth(card)
    in
      if spell = true then 
        print ("             #" ^ name)
      else print ("             " ^ name);
      print (" $" ^ (Int.toString(cost)));
      print (" @" ^ (Int.toString(attack)));
      print (" %" ^ (Int.toString(health)));
      print ("\n");
      printHand(tl list)
    end;

(*  ======= {PRINT GIVEN FIELD} =======
      takes minions or monsters list
           and prints elements
    ===================================  *) 
fun printField (list:(string*int*int)list) = 
  if null list then
    nil
    (*print ("             Field empty!\n")*)
  else
    let
      val card = hd(list)
      val name = #1(card)
      val attack = #2(card)
      val health = #3(card)
    in
      print ("             " ^ name);
      print (" @" ^ (Int.toString(attack)));
      print (" %" ^ (Int.toString(health)));
      print ("\n");
      printField(tl list)
    end;

(*  ======= {CHECK FOR CARD IN HAND} =======
       searches given hand for given name
             returns true or false
    ========================================  *)
fun checkCardH (list, name) =
  if null list then
    false
  else
    let
      val card = hd(list)
      val title = getName(card)
    in
      if (name:string) = title then true
      else checkCardH(tl list, name)
    end;

(*  ======= {CHECK FOR CARD IN FIELD} =======
       searches given field for given name
             returns true or false
    =========================================  *)
fun checkCardF (list:(string*int*int)list, name) =
  if null list then
    false
  else
    let
      val card = hd(list)
      val title = #1(card)
    in
      if (name:string) = title then true
      else checkCardF(tl list, name)
    end;

(*  ======= {GETS CARD FROM HAND} =======
      serches given hand for given name
        returns card with given name
    =====================================  *)
fun getCardH (list, name):(int*bool*string*int*int) =
  let
    val card = hd(list)
    val title = getName(card)
  in
    if name = title then card
    else getCardH(tl list, name)
  end;

(*  ======= {GETS CARD FROM FIELD} =======
      serches given field for given name
         returns card with given name
    =====================================  *)
fun getCardF (list, name):(string*int*int) =
  let
    val card = hd(list)
    val title = #1(card)
  in 
    if name = title then card
    else getCardF(tl list, name)
  end;

(*  ======= {ADD CARD TO HAND OR FIELD} =======
       adds given card to given hand or field
    ===========================================  *)
fun addCard (list, card) = 
  if null list then [card]
  else (hd list)::(addCard((tl list), card));

(*  ======= {REMOVE CARD FROM HAND} =======
      removes given card from given hand
    =======================================  *)
fun handRemove (list, card:(int*bool*string*int*int)) =
  if null list then nil
  else if (hd list) = card then (tl list)
  else (hd list)::(handRemove((tl list), card));

(*  ======= {REMOVE CARD FROM FIELD} =======
      removes given card from given field
    =======================================  *)
fun fieldRemove (list, card:(string*int*int)) =
  if null list then nil
  else if (hd list) = card then (tl list)
  else (hd list)::(fieldRemove((tl list), card));

(*  ======= {ATTACK WITH SPELL} =======
    plays spell card with specified name
      excess damage from spell card is
       applied directly to opponent
    ===================================  *) 
fun spellAtk (name, attack) =
  let
    val monster = getCardF(!monsters, name)
    val Health = #3(monster)
    val newHealth = (Health - attack)
    val extra = if newHealth < 0 then newHealth
                else 0
    val title = #1(monster)
    val damage = #2(monster)
    val updated = (title, damage, newHealth)
  in
    if newHealth <= 0 then (
      print ("\nYour opponent's \"" ^ name ^ "\" was eliminated\n");
      monsters := fieldRemove(!monsters, monster);
      if extra < 0 then (
	aiHealth := ((!aiHealth) + extra);
        print ("Additionally, your opponent's defenses were not "
               ^ "strong enough\n" ^ "They have lost " 
               ^ (Int.toString(extra * ~1))
               ^ " health points\n"))
      else
	print ("No additional damage was done\n"))
    else (
      print ("\nYour opponent's \"" ^ name ^ "\" still stands\n");
      monsters := fieldRemove(!monsters, monster);
      monsters := addCard(!monsters, updated))
  end;

(*  ======= {CHECK GIVEN PLAYED POOL} =======
    searches given played pool for given name
              returns true or false
     copy of checkCardF used for readability
    =========================================  *)
fun checkPlayed (list:(string*int*int)list, name) =
  if null list then
    false
  else
    let
      val card = hd(list)
      val title = #1(card)
    in
      if (name:string) = title then true
      else checkPlayed(tl list, name)
    end;

(* ======= {HIGHEST CARD IN AI HAND} =======
    this function will get the highest card
        avaialable for play in ai hand
        since card energies are ordered
    highest to lowest, no need to compare
              cards to each other
    ========================================  *)
fun aiHighest (list, Energy) =
  if null list then 0
  else 
    let
      val card = hd(list)
      val cost = getCost(card)
    in
      if cost <= (Energy) then cost
      else aiHighest(tl list, Energy)
    end;

(*  ======= {GET HIGHEST CARD} =======
      gets the highest available card 
            for play in ai hand
    ==================================  *)
fun getHighest (list, Cost):(int*bool*string*int*int) =
  let
    val card = hd(list)
    val cost = getCost(card)
  in
    if Cost = cost then card
    else getHighest(tl list, Cost)
  end;

(*  ======= {FIND LOWEST HEALTH} =======
      searches minion field for lowest
      health creature for ai to attack
   this is my attempt at some extra credit
  because the ai is not just making random
     moves, instead it is strategically  
    targetting the lowest health enemy in 
     hopes to inflict damage on the user
    ====================================  *)
fun findLow (list:(string*int*int)list, low) =
  if null list then low
  else
    let
      val card = hd(list)
      val Health = #3(card)
    in
      if Health < low then
        findLow(tl list, Health)
      else 
        findLow(tl list, low)
    end;

(*  ======= {GET LOWEST HEALTH CARD} =======
     returns the card of the creature with
                the least health
    ========================================  *)
fun getLow (list:(string*int*int)list, low) =
  let
    val card = hd(list)
    val Health = #3(card)
  in
    if Health = low then card
    else getLow(tl list, low)
  end;

(*  ======= {VICTORY FUNCTION FOR USER} ========
     if opponent's health is less than or equal
      to zero then the user wins and the game 
                    is exited
       otherwise game continues with message
    ============================================  *)
fun victoryU () =
  if (!aiHealth) <= 0 then (
    print("===================================================\n");
    print("       ===================================\n");
    print("                 V I C T O R Y\n");
    print("         You have defeated your opponent!\n\n"); 
    print("          Thank you for playing MLstone\n");
    print("       ===================================\n");
    print("===================================================\n");
    OS.Process.exit(OS.Process.success))
  else 
    print("Your opponent is still standing\n");

(*  ======= {VICTORY FUNCTION FOR OPPONENT} ========
     if user's health is less than or equal to zero
      then the user loses and the game is exited
        otherwise game continues with message
    ============================================  *)
fun victoryO () =
  if (!health) <= 0 then (
    print("===================================================\n");
    print("       ===================================\n");
    print("                  D E F E A T\n");
    print("             You have been defeated!\n\n");
    print("          Thank you for playing MLstone\n");
    print("       ===================================\n");
    print("===================================================\n");
    OS.Process.exit(OS.Process.success))
  else
    print("You are still standing\n");


