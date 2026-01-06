(* mlstone.sml

   Miguel Villanueva 
   CS 210            
 ----------------------------------------------------------------------
     75+ Hours To Implement
     840 Lines Of Code
     34 Functions
     Extra Things Worked On:
        - Making the AI smarter than just making random moves
	     - AI's stategy is to attack the user's
               lowest health cards
        - Greeting Banner
     Notes:
        - Each "player" begins with 17 cards
        - Found it more enjoyable to play when the AI
          hand wasn't printed
             - Otherwise user may have to scroll to
               see entire game
        - Was not sure whether a player's field needed
          to be empty for the player to be damaged
             - Made the decision to have card
               excess damage go to player  
 ----------------------------------------------------------------------
 ----------------------------------------------------------------------  *) 

use "game.sml";

val gameTurn = ref 1;
val turn = ref 1;
val energy = ref 1;
val oEnergy = ref 1;
val cardCount = ref 0;

(*  ======= {GET ENERGY FUNCTIONS} =======
          prints the current energies
         used in the gameState function
    ======================================  *)
fun getEnergyU (x) = (
  print ("  - Your Available Energy: " ^ (Int.toString (!x)) ^ "\n"));
fun getEnergyO (x) = (
  print ("  - Your Opponent's Energy: " ^ (Int.toString (!x)) ^ "\n\n"));

(*  ======= {PRINT GAME STATE} =======
       prints the current game state
    ==================================  *)
fun gameState () = (
  print ("===================================================\n");
  print ("{Game State}\n");
  print ("  - Your Health: " ^ (Int.toString (!health)) ^ "\n");
  print ("  - Opponent's Health: " ^ (Int.toString (!aiHealth)) ^ "\n");
  getEnergyU (energy);
  getEnergyO (oEnergy);
  print ("  {Playing Field}\n");
  print ("     [Name, @ Attack, % Health]\n");
  print ("        - (YOUR CREATURES)\n");
  printField(!minions);
  print ("        - (OPPONENT'S CREATURES)\n");
  printField(!monsters);
  print ("  {Hands}\n");
  print ("     [# Spell, Name, $ Cost, @ Attack, % Health]\n");
  print ("        - (YOUR HAND)\n");
  printHand(!userHand);
  print ("        - (OPPONENT'S HAND)\n");
  printHand(!aiHand);
  print ("===================================================\n")
  );

(*  ======= {GET INPUT} =======
   helper function that gets input 
    ============================  *)
fun getInput() =
case TextIO.inputLine TextIO.stdIn of
    NONE => "end of file"
  | SOME v => v;

(*  ======= {RETURN USER INPUT} =======
           Takes getInput() and 
         removes newline from input 
    ===================================  *)
fun userInput() = ( 
  let
    val str = getInput()
  in
    String.substring(str,  0, size str -1)
  end);

(*  ======= {PLAY FUNCTION} =======
    takes care of the play part of
        the getCommand function
    ===============================  *)
fun play (input) =
  if checkCardH(!userHand, input) = false then
    print ("\n***INVALID CARD***\n")
  else
    let
      val card = getCardH(!userHand, input)
      val cost = getCost(card)
      val spell = getSpell(card)
      val name = getName(card)
      val attack = getAttack(card)
      val Health = getHealth(card)
      val new = (name, attack, Health)
    in
      if cost > (!energy) then
        print ("\n***NOT ENOUGH ENERGY TO PLAY CARD***\n")
      else if spell = true then
        if null (!monsters) then (
          aiHealth := ((!aiHealth) - attack);
          energy := ((!energy) - cost);
          userHand := handRemove(!userHand, card); 
          print ("\nYour opponent could not defend against your spell\n");
          print ("They lost " ^ (Int.toString(attack))
                 ^ " health points\n") )
        else (
	  print ("\nEnter the name of your opponent's card that you want\n"
                 ^ "to use your spell on\n> ");
          let
            val enemy = userInput()
          in
            if checkCardF(!monsters, enemy) = false then
              print ("\n***INVALID CARD TO ATTACK***\n")
            else (
              spellAtk(enemy, attack);
              energy := ((!energy) - cost);
              userHand := handRemove(!userHand, card) )   
          end )
      else (
        userHand := handRemove(!userHand, card);
        energy := ((!energy) - cost);
        minions := addCard(!minions, new);
        justPlayedU := addCard(!justPlayedU, new) )
     end;

(*  ======= {EMPTY ATTACK FUNCTION} =======
    takes care of condition that opponent's
                 field is empty
          used in tandem with regular 
                attack function
    =======================================  *)
fun eAttack () = (
  print("\nYour opponent is vulnerable\n");
  print("Enter a name from your field to attack them with\n> ");
  let
    val direct = userInput()
  in
    if checkCardF(!minions, direct) = false then
      print ("\n***INVALID CARD TO ATTACK WITH***\n")
    else
      if checkPlayed(!justPlayedU, direct) = true then
        print ("\n***THIS CARD CANNOT BE PLAYED THIS TURN***\n")
      else
        let
          val minion = getCardF(!minions, direct)
          val Attack = #2(minion)
        in (
          aiHealth := (!aiHealth) - Attack;
          print ("\nYour opponent lost "
                 ^ (Int.toString(Attack))
                 ^ " health points\n") )
        end
  end );

(*  ======= {ATTACK FUNCTION} =======
    takes care of the attack part of
        the getCommand function
    =================================  *)
fun attack (enemy) =
  if checkCardF(!monsters, enemy) = false then
    print ("\n***INVALID CARD TO ATTACK***\n")
  else (
    print("\nEnter a name from your field to attack with\n> ");
    let
      val monster = getCardF(!monsters, enemy)
      val Health = #3(monster)
      val title = #1(monster)
      val damage = #2(monster)
      val input = userInput()
    in
      if checkCardF(!minions, input) = false then
        print ("\n***INVALID CARD TO ATTACK WITH***\n")
      else
        if checkPlayed(!justPlayedU, input) = true then
	  print ("\n***THIS CARD CANNOT BE PLAYED THIS TURN***\n")
        else
          let
            val card = getCardF(!minions, input)
            val Attack = #2(card)
            val newHealth = (Health - Attack)
            val extra = if newHealth < 0 then newHealth
                        else 0
            val updated = (title, damage, newHealth)
          in (
            justPlayedU := addCard(!justPlayedU, card);
            if newHealth <= 0 then (
              print ("\nYour opponent's \"" ^ title ^ "\" was eliminated\n");
              monsters := fieldRemove(!monsters, monster);
              if extra < 0 then (
                aiHealth := ((!aiHealth) + extra);
                print ("Additionally, your opponent's defenses were not "
                       ^ "stong enough\n" ^ "They have lost "
                       ^ (Int.toString(extra * ~1))
                       ^ " health points\n") )
              else
                print ("No additional damage was done\n") )
            else (
              print ("Your opponent's \"" ^ title ^ "\" still stands\n");
              monsters := fieldRemove(!monsters, monster);
              monsters := addCard(!monsters, updated) ) )
          end
    end );
 
(* ======= {GET COMMAND} =======
    reads and evaluates command 
     takes care of player turn 
   =============================  *)
fun getCommand() = (
  print("---------------------------------------------------\n");
  print("===================================================\n");
  print("{Your Turn}\n"); 
  print("   Enter a command: \n");
  print("     - Enter 'end' to end turn\n");
  print("     - Enter 'play' to play a card\n");
  print("     - Enter 'attack' to attack a card\n");
  print("     - Enter 'quit' to exit game\n");
  print("> "); 
  let
    val command = userInput()
  in
    if command = "end" then
      (turn := 0)
    else if command = "play" then (
      print ("\nEnter the name of the card you wish to play\n> ");
      let
        val input = userInput()
      in
        play(input)
      end )
    else if command = "attack" then
      if null (!monsters) then eAttack()
      else (
        print ("\nEnter the name of your opponent's card you'd" 
               ^ " like to attack\n> ");
        let
          val enemy = userInput()
        in
          attack(enemy)
        end )
    else if command = "quit" then
      (OS.Process.exit(OS.Process.success))
    else
      print "\n***INVALID COMMAND***\n"
  end
  );

(*  ======= {AI ATTACK FUNCTION} =======
        part of the ai attack phase
      like the user attack function but
           without the user input
    ====================================  *)
fun attackO (card:(string*int*int)) =
  if null (!minions) then (
    print("You were left vulnerable\n");
    let
      val Attack = #2(card)
      val title = #1(card)
    in (
      health := (!health) - Attack;
      print ("You lost " ^ (Int.toString(Attack))
             ^ " health points in result"
             ^ " of your opponent's \"" 
             ^ title ^ "\" attacking you") )
    end )
  else 
    let
      val Attack = #2(card)
      val title = #1(card)
      val first = hd(!minions)
      val fHealth = #3(first)
      val low = findLow(!minions, fHealth)
      val minion = getLow(!minions, low)
      val name = #1(minion)
      val damage = #2(minion)
      val Health = #3(minion)
      val newHealth = (Health - Attack)
      val extra = if newHealth < 0 then newHealth
                  else 0
      val updated = (name, damage, newHealth)
    in 
      if newHealth <= 0 then (
        print ("Your \"" ^ name ^ "\" was eliminated by\n"
               ^ "your opponent's \"" ^ title ^ "\"\n");
        minions := fieldRemove(!minions, minion);
        if extra < 0 then (
          health := ((!health) + extra);
          print ("Additionally, your defenses were not "
                 ^ "strong enough\n" ^ "You lost "
                 ^ (Int.toString(extra * ~1))
                 ^ " health points\n") )
        else
          print ("No additional damage was done\n") )
      else (
        print ("Your opponent attacked your \"" ^ name ^"\" with\n"
               ^ " their \""  ^ title ^ "\", but your creature"
               ^ " still stands\n");
        minions := fieldRemove(!minions, minion);
        minions := addCard(!minions, updated) )
    end;
      
(* ======= {USE MONSTERS ON FIELD} =======  
       expends opponent's attack phase
       leads into opponent's play phase
   =======================================  *)      
fun useMonsters (list) =
  if null list then
    print("Your opponent ended their attacking phase\n")
  else
    let
      val monster = hd(list)
    in (
      attackO(monster);
      useMonsters(tl list) )
    end;  

(*  ======= {AI PLAY FUNCTION} =======
    because 'play' happens right after
    'attack', there is no need to keep
       track of what cards are not
           available for play
    ==================================  *)
fun playO (card) =
  let
    val cost = getCost(card)
    val spell = getSpell(card)
    val name = getName(card)
    val attack = getAttack(card)
    val Health = getHealth(card)
    val new = (name, attack, Health)
  in
    if spell = true then
      if null(!minions) then (
        health := ((!health) - attack);
        oEnergy :=((!oEnergy) - cost);
        aiHand := handRemove(!aiHand, card);
        print("Your opponent played the spell \"" ^ name ^ "\"\n");
        print("You could not defend against your opponent's spell\n");
        print("You lost " ^ (Int.toString(attack)) 
              ^ " health points\n") )
      else (
        aiHand := handRemove(!aiHand, card);
        oEnergy := ((!oEnergy) - cost);
        let
          val first = (hd(!minions)):(string*int*int)
          val fHealth = #3(first)
          val low = findLow(!minions, fHealth)
          val minion = getLow(!minions, low)
          val title = #1(minion)
          val damage = #2(minion)
          val mHealth = #3(minion)
          val newHealth = (mHealth - attack)
          val extra = if newHealth < 0 then newHealth
                      else 0
          val updated = (title, damage, newHealth)
       in
         if newHealth <= 0 then (
           print("Your opponent played the spell \"" ^ name ^ "\"\n");
           print("They eliminated your \"" ^ title ^ "\"\n");
           minions:= fieldRemove(!minions, minion);
           if extra < 0 then (
             health := ((!health) + extra);
             print ("Additionally, your defenses were not "
                    ^ "strong enough\n" ^ "You lost "
                    ^ (Int. toString(extra * ~1))
                    ^ " health points\n") ) 
           else
	     print ("No additional damage was done\n") )
         else (
           print("Your opponent played the spell \"" ^ name ^ "\"\n");
           print("Your opponent attacked your \"" ^ title ^"\" but\n"
                 ^ " your creature still stands\n");
           minions := fieldRemove(!minions, minion);
           minions := addCard(!minions, updated) )
       end )
    else (
      print("Your opponent played their \"" ^ name ^ "\"\n");
      aiHand := handRemove(!aiHand, card);
      oEnergy := ((!oEnergy) - cost);
      monsters := addCard(!monsters, new) )
  end;

(*  ======= {AI EXPEND ALL ENERGY} =======
     makes the ai play all possible cards
     starting at the highest energy until
       their energy is depleted or until
      no more cards can be played due to
          a lack in energy or cards
    ======================================  *) 
fun expendEnergy (Energy:int ref) = 
  let
    val high = aiHighest(!aiHand, !Energy)
  in
    if high = 0 then (
      print("Your opponent ended their playing phase\n");
      print("Your opponent expended " 
            ^ (Int.toString((!gameTurn) - (!oEnergy))) ^ " out of "
            ^ (Int.toString(!gameTurn)) ^ " energy\n");
      print("Your opponent played a total of "
            ^ (Int.toString(!cardCount)) ^ " cards during"
            ^ " their turn\n") )
    else
      let
        val card = getHighest(!aiHand, high)
      in (
        cardCount := (!cardCount) + 1;
        playO(card);
        expendEnergy(Energy) )
      end
  end;   

(*          =================
    ======= MLSTONE GAME LOOP =======
            =================          *)
val _ = print("===================================================\n");
val _ = print(" _____ ------------------------------------- _____ \n");
val _ = print("|     | =================================== |     |\n");
val _ = print(" | | |          ===================          | | |\n");   
val _ = print(" | | |  # $ @ %    M L S T O N E    % @ $ #  | | |\n");
val _ = print(" | | |          ===================          | | |\n");
val _ = print(" | | |                Welcome!               | | |\n");
val _ = print("|_____| =================================== |_____|\n");
val _ = print("       -------------------------------------       \n");
while (!gameTurn > 0) do (
  turn := 1;
  energy := (!gameTurn);
  oEnergy := (!gameTurn);
  justPlayedU := [];
  cardCount := 0;
  gameState();
  while (!turn > 0) do (
    getCommand();
    print("===================================================\n");
    victoryU();
    victoryO();
    gameState() );
  print ("{Opponent's Turn}\n\n");
  if null (!monsters) then 
    print("Your opponent could not attack this round\n")
  else 
    useMonsters(!monsters);
  expendEnergy(oEnergy);
  victoryU();
  victoryO();
  gameTurn := (!gameTurn) + 1 );

