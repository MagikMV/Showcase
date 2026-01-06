void showProgramHeader();
void printGlobalVariables();
void room1();
void room2();
void room3();
void room4();
void room5();
void room6();
void gameEnd();


#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//***Structure that refers to "your" information as the player***
typedef struct your
{
    char firstName[50];
    char middleName[50];
    char lastName[50];
}your;

//***Functions that refer to "your" structure***
void playerInformation(your & user_input);
void print_playerInfo(your & user_input);

//***Global variables***
int energy = 10;
int health = 100;
your information; // Made global to use across functions

int main()
{
    showProgramHeader();
    cout << endl << "***A DARK ROOM***" << endl;
    printGlobalVariables();
    room1();
    cout << endl << "***A VAST DESERT***" << endl;
    printGlobalVariables();
    room2();
    cout << endl << "***A CARTOONISH LAND***" << endl;
    printGlobalVariables();
    room3();
    cout << endl << "***A BUSY CASINO***" << endl;
    printGlobalVariables();
    room4();
    cout << endl << "***A... WELL... SPACE: YOU ARE IN SPACE***" << endl;
    printGlobalVariables();
    room5();
    cout << endl << "***A STREET CORNER***" << endl;
    printGlobalVariables();
    room6();
    cout << endl << "***A BUS RIDE***" << endl;
    gameEnd();
    cout << endl << "     ***THE END***" << endl;
    cout << "***THANKS FOR PLAYING***" << endl << endl;
}
void showProgramHeader()
{
    cout << "Miguel Villanueva \nCS 120 Section 6 \nMarch 10, 2019 \nHomework Number 7" << endl;
}

void printGlobalVariables ()
{
    cout << endl << "   Energy remaining: " << energy << endl;
    cout << "   Health remaining: " << health << endl;
    if (energy == 0 && health == 0)
    {
        cout << "   GAME OVER" << endl;
    }
}

void playerInformation(your & user_input)
{
    cout << endl << "First name: ";
    cin >> user_input.firstName;
    cout << "Middle name: ";
    cin >> user_input.middleName;
    cout << "Last name: ";
    cin >> user_input.lastName;
}

void print_playerInfo(your & user_input)
{
    cout << user_input.firstName << " " << user_input.middleName << " " << user_input.lastName << endl;
}

void room1()
{
    int wakingAction;
    int chairAction;
    int leavingAction;

    cout << endl << "You wake up in a dark room and can't see a thing." << endl;
    cout << "What do you do? What CAN you do?" << endl;
    cout << "You think to FEEL around, but maybe it is best to stay STILL." << endl;
    cout << "Enter 1 to FEEL around, or 2 to stay STILL." << endl;
    cin >> wakingAction;

    do
    {
        if (wakingAction == 1)
        {
            cout << endl << "You decided to FEEL around." << endl;
            cout << "However, you realize you are unable to move your arms or legs." << endl;
            cout << "You realize your wrists and ankles feel tight, as if they are being held down by something." << endl;
            cout << "Before you can give it much thought, a light appears." << endl;

            break;
        }
        else if (wakingAction == 2)
        {
            cout << endl << "You decided to stay STILL." << endl;
            cout << "However, your wrists and ankles feel tight, as if they are being held down by something." << endl;
            cout << "Before you can give it much thought, a light appears." << endl;

            break;
        }
        else
        {
            cout << "Enter 1 to FEEL around, or 2 to stay STILL." << endl;
            cin >> wakingAction;
        }
    }
    while (wakingAction != 1 || wakingAction != 2);

    cout << endl << "The room around you slowly illuminates in a blue glow." << endl;
    cout << "You realize the light is pouring in from the bottom of a large window." << endl;
    cout << "Actually, you start to see that the entire wall in front of you is one big window, " << endl;
    cout << "its sleek blinds, which once shrouded you in darkness rising." << endl;
    cout << "As more and more of the outside world becomes visible, you begin to look out the window." << endl;

    cout << endl << "As you understand it, you are in some kind of skyscraper, hundreds of feet above the ground." << endl;
    cout << "The urban landscape below radiates a spectrum of light against the night sky as rain pours down relentlessly." << endl;
    cout << "Yet, all that seems to light the room is a culminating blue glow from the city beneath." << endl;
    cout << "The view outside the window reminds you of Blade Runner, and you wonder why." << endl;
    cout << "Do you even know what Blade Runner is? How did you get here?" << endl;

    cout << endl << "In the now brightened room, you look down and realize you are binded in a chair, " << endl;
    cout << "metal clasps around your wrists and ankles. This explains the tightness you were feeling earlier." << endl;
    cout << "But... what about the blinds." << endl;
    cout << "The blinds rising couldn't have been your doing. So then who... or what?" << endl;

    cout << endl << "You seem to be alone in the room." << endl;
    cout << "Odd... am I being watched, you think to yourself." << endl;
    cout << "Regardless, you feel the need to get free, but also think it might be useless." << endl;
    cout << "Perhaps it is better to save your energy, but then again what else are you gonna do?" << endl;

    cout << endl << "Will you WAIT? Or will you TRY to wriggle free of your binds?" << endl;
    cout << "Enter 1 to WAIT or 2 to TRY." << endl;
    cin >>  chairAction;

    do
        if (chairAction == 1)
        {
            cout << endl << "You chose to WAIT" << endl;
            cout << "Because of this, the metal clasps which binded you release, and you are free." << endl;
            cout << "Is this because I was obedient or something, you start to think." << endl;

            energy = energy - 0;
            health = health - 0;
            printGlobalVariables();

            cout << endl << "Without pondering it too much, you immediately stand up, and take in your surroundings." << endl;

            break;
        }
        else if (chairAction == 2)
        {
            cout << endl << "You chose to TRY and wriggle free of your binds." << endl;
            cout << "You exert as much force as you can against the metal clasps, but end up falling over in the chair, " << endl;
            cout << "hurting yourself, and wasting energy" << endl;

            energy = energy - 1;
            health = health - 5;
            printGlobalVariables();

            cout << endl << "To your surprise however, the clasps release, and you are free." << endl;
            cout << "Was that my doing, or someone else's, you start to think." << endl;

            cout << endl << "Without pondering it too much, you immediately stand up, and take in your surroundings." << endl;

            break;
        }
        else
        {
            cout << "Enter 1 to WAIT, or 2 to TRY." << endl;
            cin >> chairAction;
        }
    while (chairAction != 1 || chairAction != 2);

    cout << "The room you are in looks like it belonged to a CEO of a large corporation, " << endl;
    cout << "and you see that there is a single DOOR leading out of the room behind you" << endl;

    cout << endl << "However, you don't know if any of this is real, why are you even here." << endl;
    cout << "Instead of taking the door, you consider JUMPING out of the window, but what would that accomplish?" << endl;
    cout << "Will you use the DOOR, or JUMP out of the window?" << endl;
    cout << "Enter 1 to use the DOOR, or 2 to JUMP out of the window." << endl;
    cin >> leavingAction;

    do
    {
        if (leavingAction == 1)
        {
            cout << endl << "You chose to use the DOOR." << endl;
            cout << "Although, to your surprise, the door opens up to a vast desert." << endl;
            cout << "Before you have time to think about the situation, you are warped out of the door way." << endl;
            cout << "You land roughly on the coarse desert sand, hurting yourself." << endl;

            energy = energy - 0;
            health = health - 10;
            printGlobalVariables();

            break;
        }
        else if  (leavingAction == 2)
        {
            cout << endl << "You chose to JUMP out of the window" << endl;
            cout << "You sprint toward the window at full speed, and cross your arms hoping to break the glass." << endl;
            cout << "As you make contact with the window you unexpectedly warp through it." << endl;
            cout << endl << "You look all around you, and notice you are now in a desert... a pretty big one by the looks of it" << endl;
            cout << "You are luckily unscathed by glass shards, but sprinting took some energy out of you." << endl;

            energy = energy - 1;
            health = health - 0;
            printGlobalVariables();

            break;
        }
        else
        {
            cout << "Enter 1 to use the DOOR, or 2 to JUMP out of the window." << endl;
            cin >> leavingAction;
        }
    }
    while (leavingAction != 1 || leavingAction != 2);
}

void room2()
{
    int desertAction;
    int remoteAction;

    cout << endl << "The desert air is hot and dry, and you immediately regret your decision to leave the dark room." << endl;
    cout << "The sun beats down on you and you swear you can feel your skin sizzle. You won't last long out here." << endl;
    cout << "You have to find a way out before it's too late. There has to be an explanation for what's going on." << endl;

    cout << endl << "You think to WANDER the desert, however you also think to sit and MEDITATE, but what good would that do." << endl;
    cout << "Press 1 to WANDER the desert, or 2 to MEDITATE." << endl;
    cin >> desertAction;

    do
    {
        if (desertAction == 1)
        {
            cout << endl << "You chose to WANDER the desert." << endl;
            cout << "You walk aimlessly around the desert for hours and slowly lose energy." << endl;
            cout << "Just as you are about to give up, you miraculously stumble upon a remote." << endl;

            energy = energy - 2;
            health = health - 0;
            printGlobalVariables();

            cout << endl << "The remote is a simple one, but perhaps it is your way out?" << endl;

            break;
        }
        else if (desertAction == 2)
        {
            cout << endl << "You chose to MEDITATE." << endl;
            cout << "Closing your eyes, hours begin to pass, and you start to wonder if anything will happen." << endl;
            cout << "However, just as you think this, a remote miraculously falls out of the sky, and unfortunately so, onto your head." << endl;

            energy = energy - 0;
            health = health - 10;
            printGlobalVariables();

            cout << endl << "Your hand instantly shoots up to feel around the affected area and you notice a small bump." << endl;
            cout << "You wince in pain, however, you realize the remote could be your way out!" << endl;

            break;
        }
        else
        {
            cout << "Press 1 to WANDER the desert, or 2 to MEDITATE." << endl;
            cin >> desertAction;
        }
    }
    while (desertAction != 1 || desertAction != 2);

    cout << endl << "With excitement, you reach out for the remote, and scoop it up." << endl;
    cout << "You turn the remote over in your hand and come across nothing but a single red button on it." << endl;
    cout << "What to do... PRESS the red button in hopes to escape the desert, or LEAVE the remote behind in case it's a trap." << endl;

    cout << endl << "Enter 1 to PRESS the red button, or 2 to LEAVE the remote behind." << endl;
    cin >> remoteAction;

    do
    {
        if (remoteAction == 1)
        {
            cout << endl << "You chose to PRESS the red button." << endl;
            cout << "Nothing happens... you press it again... nothing... again and again..." << endl;
            cout << "You toss the remote away in frustration." << endl;

            cout << endl << "Just as you do this however, you hear a massive explosion behind you." << endl;
            cout << "You turn around only to see an enormous mushroom cloud." << endl;
            cout << "What have you done, you ask yourself." << endl;

            cout << endl << "Without thinking you start to make a run for it." << endl;
            cout  << "You start to lose energy, but that's the least of your worries!" << endl;

            energy = energy - 1;
            health = health - 0;
            printGlobalVariables();

            cout << endl << "You run away in desperation but you know you can't outrun the blast." << endl;
            cout << "You stop to look back, and just as you do, you see the blast fast approaching." << endl;
            cout << "You stand still, ready to be hit, but you warp away in the nick of time." << endl;

            cout << endl << "You gather you're breath, and look up." << endl;
            cout << "It seems you are in a classroom... but something isn't quite right... everything is... cartoonish." << endl;

            break;
        }
        else if (remoteAction == 2)
        {
            cout << endl << "You chose to LEAVE the remote behind." << endl;
            cout << "Dropping the remote, you turn and begin to walk away, feelings of defeat gripping at your inner core." << endl;
            cout << "However, as you hang your head in sorrow, a massive explosion goes off." << endl;

            cout << endl << "You turn towards the explosion only to be met by an enormous mushroom cloud." << endl;
            cout << "You think this is it, and so you assume your loss." << endl;
            cout << "The blast of the explosion encloses upon you, and just as you feel the impact, you warp away." << endl;

            cout << endl << "You barely escaped the blast, but you've still been affected by its impact." << endl;
            cout << "The effects are not visible, but you feel weaker... maybe radiation damage?" << endl;

            energy = energy - 0;
            health = health - 20;
            printGlobalVariables();

            cout << endl << "On the bright side, you are still conscious and able to take your surroundings in." << endl;
            cout << "And so you do just that, but by the looks of it you are in nothing more than a classroom, " << endl;
            cout << "but something is off... everything is... cartoonish." << endl;

            break;
        }
        else
        {
            cout << "Enter 1 to PRESS the red button, or 2 to LEAVE the remote behind." << endl;
            cin >> remoteAction;
        }
    }
    while (remoteAction != 1 || remoteAction != 2);
}

void room3()
{
    int answersCorrect = 0;
    int firstNumber;
    int secondNumber;
    int sum = 0;
    int calculation;

    cout << endl << "You notice you are sitting in a desk, an awfully cartoony one at that." << endl;
    cout << "And before you can really grasp where you are, children come flooding into the classroom, followed by a teacher." << endl;
    cout << "It's as if the kids have just come in from recess, but that can't be, you're done with grade school..." << endl;

    cout << endl << "But, you look down... a child's body... your body, all in a cartoonish charactercher." << endl;
    cout << "You don't choose to question this however. You have to find a way out. You have to find some answers." << endl;
    cout << "You choose to focus into the classroom lesson, but you can't understand what the teacher is saying!" << endl;

    cout << endl << "Wah-wa wha waaa wha wa wha wha wha..." << endl;
    cout << "Is this an episode of Charlie Brown, you ask yourself?!" << endl;

    cout << endl << "You feel hopeless but notice that today's lesson is math. Surely you should be able to understand!" << endl;
    cout << "It seems the class is learning addition today, and from what you can gather on the board, " << endl;
    cout << "each person MUST get three addition problems correct to go home for the day! This is your only choice." << endl;

    cout << endl << "You have to find out what's happening to you.. why it's happening to you." << endl;

    cout << endl << "The teacher writes a list of math problems on the board, along with a tally counter for each student in the class." << endl;
    cout << "Get your tally count to THREE to leave the classroom." << endl;

    while (answersCorrect < 3)
    {
        srand(time(NULL));
        firstNumber = rand() % 50 + 1;
        secondNumber = rand() % 50 + 1;
        sum = firstNumber + secondNumber;
        cout << endl << "The teacher asks what " << firstNumber << " plus " << secondNumber << " is." << endl;
        cout << "You raise your hand to answer and say: ";
        cin >> calculation;

        if (calculation == sum)
        {
            cout << endl << "That's right!" << endl;
            answersCorrect = answersCorrect + 1;
            cout << "Your tally count is: " << answersCorrect << endl;
        }
        else
        {
            cout << endl << "Wrong! Don't forget you can't leave until you get three right!" << endl;
            answersCorrect = answersCorrect + 0;
            cout << "Your tally count is: " << answersCorrect << endl;
        }
    }

    cout << endl << "Finally! Your tally count is THREE!" << endl;
    cout << "You get out of your desk jumping with joy, and strangely enough, you feel like a kid again." << endl;
    cout << "However, it's only right given your current cartoony kid appearance." << endl;

    cout << endl << "You go to open the door and just as you do, you are instantly warped away." << endl;
    cout << endl << "Returned to your normal body, and by the looks of it, a seemingly real world, " << endl;
    cout << "you take a look around you. And without a doubt, you know you are in a casino." << endl;
}

void room4()
{
    int casinoAction;

    cout << endl << "The casino floor is bustling with people, cigarette smoke fills the air, and noise is found in every direction." << endl;
    cout << "From slot machines, to dealers shuffling cards, you are instantaneously immersed in the casino life." << endl;
    cout << "You are dazzled by all of the lights and even feel tempted to play a game or two." << endl;

    cout << endl << "But... what'll your exit strategy be this time?" << endl;
    cout << "As far as you know, you have no clue why any of this is happening," << endl;
    cout << "much less how you are traversing through different worlds, spaces, and times." << endl;

    cout << endl << "Will you WAIT for something to happen, or will you WALK around in hopes of finding something?" << endl;
    cout << "Press 1 to WAIT, or 2 to WALK around." << endl;
    cin >> casinoAction;

    do
    {
        if (casinoAction == 1)
        {
            cout << endl << "You chose to WAIT." << endl;
            cout << "However, you realize this was probably not the best move." << endl;
            cout << "The casino's filled with TONS of people, and you chose to stand in the middle of it all." << endl;

            cout << endl << "People zoom past you and give you weird looks." << endl;
            cout << "And before you know it you are amongst a crowd of people." << endl;
            cout << "As if caught in a wave pool, you are bumped into over and over again." << endl;

            cout << endl << "Eventually, you are spit out of the crowd, but you suffered a couple scrapes and bruises." << endl;

            energy = energy - 0;
            health = health - 10;
            printGlobalVariables();

            cout << endl << "Regardless, you are still standing, and interestingly enough, you feel you have reached your exit strategy." << endl;

            break;
        }
        else if (casinoAction == 2)
        {
            cout << endl << "You chose to WALK around." << endl;
            cout << "You have no idea where to go but continue walking every-which-way." << endl;

            cout << endl << "You walk for hours upon hours... or, you can't really tell, since casino are all about..." << endl;
            cout << "Taking your money? Well... that, but more so illusion, keeping you for as long as possible." << endl;
            cout << "Long story short is you feel tired because of all the walking." << endl;

            energy = energy - 2;
            health = health - 0;
            printGlobalVariables();

            cout << endl << "However, you finally discover something promising. You think it very well could be your exit strategy." << endl;

            break;
        }
        else
        {
            cout << "Press 1 to WAIT, or 2 to WALK around." << endl;
            cin >> casinoAction;
        }
    }
    while (casinoAction != 1 || casinoAction != 2);

    cout << endl << "Before you is a space themed slot machine." << endl;
    cout << "Without any money it seems pretty useless, but your gut feeling is to pull the slot machine's handle." << endl;
    cout << "As if the rocket shaped handle would propel you up to space, you give it a good tug." << endl;

    cout << endl << "To no avail, you simply make a fool of yourself in front of seemingly thousands of people." << endl;
    cout << "You know this must be the way, but how are you supposed to... advance for lack of a better word." << endl;

    cout << endl << "You look around, but see no obvious solutions" << endl;
    cout << "You decide you are done pondering decisions, and continue tugging on the handle as a last ditch effort." << endl;
    cout << "None of this is real anyways, you think." << endl;

    cout << endl << "Although, you make quite the scene regardless of it being real or not." << endl;
    cout << "You are eventually approached by a security guard." << endl;
    cout << "This isn't good, you think. You start to tug harder, going as far as putting both legs on the slot machine." << endl;

    cout << endl << "With the whole of your body weight, you pull as hard as you can. However this is a no go." << endl;
    cout << "For SOME reason... the security officer sees this as a threat and pulls their taser out." << endl;
    cout << "Without warning the officer pulls the trigger." << endl;

    cout << endl << "Having both feet up, you are unable to dodge the shot." << endl;
    cout << "What predicament have you gotten yourself into now?" << endl;
    cout << "This whole SITUATION has made you do drastic things, but to no surprise of your own, you are warped away just in time." << endl;
}

void room5()
{
    cout << endl << "Actual space..." << endl;
    cout << "While it isn't a surprise, you certainly weren't expecting this." << endl;
    cout << "The only thing to make this crazier would be Neil DeGrasse Tyson's narration." << endl;

    cout << endl << "But of course that would be too much to ask!" << endl;
    cout << "You are driven mad and want answers!" << endl;

    cout << endl << "You look around, and notice you are floating in total nothingness." << endl;
    cout << "Magically, you have been put into a spacesuit, of course..." << endl;

    cout << endl << "When will this end! Might as well make me play Rock, Paper, Scissors against a space monkey, you think!" << endl;
    cout << "And *poof* a space monkey sporting their very own spacesuit appears before you." << endl;

    cout << endl << "You are dumbfounded... however you think to just get it over with." << endl;
    cout << "The space monkey signals to you a best two out of three." << endl;
    cout << "You both assume the position, but you start to fear the outcome in which you lose... what could happen?" << endl;

    int yourMove; // Your move as the player
    int spaceMonkeyMove; // The space monkey's move
    int yourPoints = 0; // Points of Player 1
    int spaceMonkeyPoints = 0; // Points of Player 2
    int rounds = 3;

    cout << endl << "Press 1 for ROCK, 2 for PAPER, or 3 for SCISSORS." << endl;
    cout << "Remember, best two out of three! Just try not lose!" << endl;


    while (rounds > 0)
    {
            srand(time(NULL));
            spaceMonkeyMove = rand() % 3 + 1;
            cout << endl << "Enter your move: ";
            cin >> yourMove;

            if (yourMove >= 1 && yourMove <= 3) // Given a valid move
            {
                //***WAYS THE PLAYER CAN WIN

                if (yourMove == 1 && spaceMonkeyMove == 3)
                {
                    cout << "Your move: ROCK" << endl;
                    cout << "Space Monkey's move: SCISSORS" << endl;
                    cout << "ROCK beats SCISSORS" << endl;
                    cout << "Point to You" << endl;
                    yourPoints = yourPoints + 1;
                    rounds--;

                    cout << endl << "Your points: " << yourPoints << endl;
                    cout << "Space Monkey's points: " << spaceMonkeyPoints << endl;
                }
                if (yourMove == 2 && spaceMonkeyMove == 1)
                {
                    cout << "Your move: PAPER" << endl;
                    cout << "Space Monkey's move: ROCK" << endl;
                    cout << "PAPER beats ROCK" << endl;
                    cout << "Point to You" << endl;
                    yourPoints = yourPoints + 1;
                    rounds--;

                    cout << endl << "Your points: " << yourPoints << endl;
                    cout << "Space Monkey's points: " << spaceMonkeyPoints << endl;
                }
                if (yourMove == 3 && spaceMonkeyMove == 2)
                {
                    cout << "Your move: SCISSORS" << endl;
                    cout << "Space Monkey's move: PAPER" << endl;
                    cout << "SCISSORS beats PAPER" << endl;
                    cout << "Point to You" << endl;
                    yourPoints = yourPoints + 1;
                    rounds--;

                    cout << endl << "Your points: " << yourPoints << endl;
                    cout << "Space Monkey's points: " << spaceMonkeyPoints << endl;
                }

                //***WAYS THE SPACE MONKEY CAN WIN

                if (spaceMonkeyMove == 1 && yourMove == 3)
                {
                    cout << "Your move: SCISSORS" << endl;
                    cout << "Space Monkey's move: ROCK" << endl;
                    cout << "ROCK beats SCISSORS" << endl;
                    cout << "Point to the Space Monkey" << endl;
                    spaceMonkeyPoints = spaceMonkeyPoints + 1;
                    rounds--;

                    cout << endl << "Your points: " << yourPoints << endl;
                    cout << "Space Monkey's points: " << spaceMonkeyPoints << endl;
                }
                if (spaceMonkeyMove == 2 && yourMove == 1)
                {
                    cout << "Your move: ROCK" << endl;
                    cout << "Space Monkey's move: PAPER" << endl;
                    cout << "PAPER beats ROCK" << endl;
                    cout << "Point to the Space Monkey" << endl;
                    spaceMonkeyPoints = spaceMonkeyPoints + 1;
                    rounds--;

                    cout << endl << "Your points: " << yourPoints << endl;
                    cout << "Space Monkey's points: " << spaceMonkeyPoints << endl;
                }
                if (spaceMonkeyMove == 3 && yourMove == 2)
                {
                    cout << "Your move: PAPER" << endl;
                    cout << "Space Monkey's move: SCISSORS" << endl;
                    cout << "SCISSORS beats PAPER" << endl;
                    cout << "Point to the Space Monkey" << endl;
                    spaceMonkeyPoints = spaceMonkeyPoints + 1;
                    rounds--;

                    cout << endl << "Your points: " << yourPoints << endl;
                    cout << "Space Monkey's points: " << spaceMonkeyPoints << endl;
                }

                //***YOU AND THE SPACE MONKEY MADE THE SAME MOVE***

                if (yourMove == spaceMonkeyMove)
                {
                    cout << "Oops, same move, replay the round!" << endl;
                    cout << "But, you know what they say... Great minds think alike." << endl;
                    rounds = rounds + 1;
                }
            }
            else // Given an invalid move
            {
                cout << "Unknown move" << endl;
                cout << "Enter 1, 2, or 3" << endl;
                rounds = rounds + 1;
            }

            //***OUTCOMES***

            if (yourPoints == 2) // You win
            {
                cout << endl << "You won Rock, Paper, Scissors with " << rounds << " round(s) remaining!" << endl;
                cout << "The Space Monkey gives you a thumbs up!" << endl;
                cout << "This is kind of heart warming for you, and as you slowly warp away, you feel kinda bad." << endl;

                cout << endl << "For a moment, you stop questioning your situation, and begin to actually appreciate it all." << endl;
                cout << "In a now calmed state, you are determined to find out why any of this is happening to you." << endl;
                cout << "With a final wave goodbye to the Space Monkey, you warp away." << endl;

                break;
            }
            if (spaceMonkeyPoints == 2) // Space monkey wins
            {
                cout << endl << "The Space Monkey won Rock, Paper, Scissors with " << rounds << " round(s) remaining!" << endl;
                cout << "Uh oh... What is going to happen, you think, your realized fear setting in." << endl;
                cout << "The monkey raises its arm, and forms a shape of an L with its hand." << endl;

                cout << endl << "Raising its hand to its forehead, it sticks its tongue out at you." << endl;
                cout << "This is worse than you thought, greater than any pain you've felt before." << endl;

                energy = energy - 0;
                health = health - 40;
                printGlobalVariables();

                cout << endl << "In the end however, you appreciate this moment and laugh to yourself as you slowly start to warp away." << endl;
                cout << "In a now calmed state, you are determined to find out why any of this is happening to you." << endl;
                cout << "With a final wave goodbye to the Space Monkey, you warp away." << endl;

                break;
            }
        }

}

void room6()
{
    cout << endl << "You look around. Your feet on hard concrete, you think you are back on Earth... or wherever seems like Earth." << endl;
    cout << "A concrete jungle surrounds you, and directly in front of you is a street corner." << endl;
    cout << "You approach the street corner and see a panhandler all alone." << endl;

    cout << endl << "It looks to be around dusk, so you begin to wonder why they are out at this time." << endl;
    cout << "However, you have a feeling they have some answers to your situation." << endl;
    cout << "You approach them, and try to have a conversation with them." << endl;

    cout << endl << "Although, they don't answer to anything you pose." << endl;
    cout << "Instead, they ask you what your name is after every question you have." << endl;
    cout << "You have a feeling they are holding out on information." << endl;

    cout << endl << "You pace back and forth before them, and decide if you should tell them your name." << endl;
    cout << "You don't want to give them whatever advantage they are seeking so you decide to give them a fake name." << endl;

    cout << endl << "They ask you again, what's your name?" << endl;
    cout << "You stop pacing, and look them in the eye." << endl;
    cout << "Alright here's my name, you begin: " << endl;

    playerInformation(information);

    cout << endl << "Interesting, the panhandler says." << endl;
    cout << "Before you can ask him anything more, he vanishes before your eyes..." << endl;

    cout << endl << "You have no idea what to do, but you start by peering around both corners of the street." << endl;
    cout << "Were they some sort of magician, you start to think..." << endl;
    cout << "You look around wildly, thoughts racing through your mind, you can't handle it... can't fathom it." << endl;
    cout << "You pass out." << endl;
}

void gameEnd()
{
    cout << endl << "You wake up on a public transportation bus."  << endl;
    cout << "Your eyes slowly opening like the blinds in the dark room (maybe it really was you who opened the blinds)." << endl;
    cout << "But what about the desert? The remote? What of the classroom and casino? SPACE?! Like hello?" << endl;
    cout << "Kukoo much... but... maybe it was just a dream... all of it... just. a. dream." << endl;

    cout << endl << "As you think this however, you look out the window and see the panhandler from your quote unquote: dream." << endl;
    cout << "The bus rolls to a stop and you decide to get off, walking at a fairly brisk pace." << endl;
    cout << "You slow down before the panhandler, and simultaneously, you notice this is the exact street corner as your... dream." << endl;

    cout << endl << "You approach the panhandler, and they instantly recognize you." << endl;
    cout << "Ah if it isn't ";

    print_playerInfo(information);

    cout << endl << "Or is that even your real name, the panhandler says?" << endl;

    cout << endl << "How do they know, you think to yourself?" << endl;

    cout << endl << "Why don't you tell me your real name? Then maybe I can give you some answers, the panhandler tell you." << endl;

    cout << endl << "This is all too strange, but you decide you have nothing to lose." << endl;
    cout << "You choose to tell the panhandler your real name this time." << endl;

    playerInformation(information);

    cout << endl << "As I thought, they say." << endl;

    cout << endl << "What does the panhandler mean?" << endl;

    cout << endl << "The panhandler says to you: you are simply playing game..." << endl;
    cout << "In fact, you are simply playing a game made by you, ";

    print_playerInfo (information);

    cout << endl << "Pointing at you, the panhandler goes on: You are simply playing a game made by you, for you." << endl;
    cout << "Additionally, I know that this game is for a class, and it is simply an assignment." << endl;

    cout << endl << "You cringe at this fact and lose all energy, so much so that you are unable to stand any longer." << endl;
    cout << "You fall to the ground, and the panhandler comes nearer to you, leaning over your body." << endl;

    energy = 0;
    health = health - 0;
    printGlobalVariables();

    cout << endl << "Continuing, the panhandler says: furthermore, this dialogue we're having is nothing more than you talking to yourself." << endl;

    cout << endl << "It can't be, you think... Who is this person?" << endl;
    cout << "As you think this, the panhandler comes in closer" << endl;

    cout << endl << "You think to cover your ears, but you have no energy. You can't move." << endl;

    cout << endl << "The panhandler finishes the conversation by saying: I'm you." << endl;

    cout << endl << "Your mind *explodes*" << endl;

    health = 0;
    printGlobalVariables();

    cout << endl << "Neil DeGrasse Tyson's narration out of nowhere: And what the player didn't know, " << endl;
    cout << "was that, what they perceived as their dreams, was actually just their imagination." << endl;
    cout << "That's all for this week folks, we'll catch you next time, on NOVA ScienceNow: Breaking The Fourth Wall." << endl;
}
