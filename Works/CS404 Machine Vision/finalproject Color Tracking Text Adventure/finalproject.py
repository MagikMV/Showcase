# finalproject.py
#
# Miguel Villanueva
# November 30, 2020
#
# Program Description:
#   Text based adventure game using color tracking controls. It is the player's discretion that will
#   lead them to victory or defeat. Go NORTH, EAST, SOUTH, or WEST to survive the storming blizzard!
#
# Game Title:
#   STORMING COLOR
#
# Game Meaning:
#   This 332 lined program plays out to emulate my college experience and sort of my life motif. I've
#   always found that if I continued to push forward, even in a roundabout way, as long as I believed
#   in myself, I would accomplish what I set out to do. However, if I backtracked, it would often end
#   up as a detriment. Since then, I've hoped to continue to do what I can! And that's how you win 
#   this game. You are fed prompts that say you are tired and maybe you should turn back, but to me,
#   you have to believe that you're on the right path, and you should see it through. And if it turns
#   out to be a dead end (metaphorically speaking): it wasn't meant to be.
#
# Sources:
#   https://medium.com/easyread/mouse-control-for-shooting-game-using-opencv-and-python-452c3446d1a3

import os
import cv2
import numpy as np
import datetime
import time

#  Change Working Directory
os.chdir("A:\\MicrosoftVSCode\\CS404\\finalproject")

#  Function For Null Statement
def nothing(x):
    pass

#  Function For Opposite Of Previous Direction
def opposite(previous):
    if previous == "North":
        return "South"
    elif previous == "East":
        return "West"
    elif previous == "South":
        return "North"
    elif previous == "West":
        return "East"

#  cv2.CAP_DSHOW Used To Avoid Warning And Provide Better Video Quality
vs = cv2.VideoCapture(0, cv2.CAP_DSHOW)

#  Input Must Be Held For At Least 1.7 Seconds
oCheck = 0    #  Initialize check for ORANGE
yCheck = 0    #  Initialize check for YELLOW 
gCheck = 0    #  Initialize check for GREEN
bCheck = 0    #  Initialize check for BLUE
pCheck = 0    #  initialize check for PINK

#  Intial Input Time Declarations
oLast = datetime.datetime.now()    #  Orange
yLast = datetime.datetime.now()    #  Yellow
gLast = datetime.datetime.now()    #  Green
bLast = datetime.datetime.now()    #  Blue
pLast = datetime.datetime.now()    #  Pink

#  Variables For Resetting Input
elapsed = datetime.datetime.now()
last = datetime.datetime.now()
reset = elapsed - last

#  'Quit' Flag Signaled By Pink Marker
pQuit = 0

#  Default Direction
direction = "none"

#  Game Start
print("         ====================================")
print("           _   _  ==================  _   _  ")
print("          //  //    STORMING COLOR    \\\\  \\\\")
print("          \\\\  \|  ==================  |/  // ")
print("          |/           The Game           \| ")
print("              -------            -------     ")
print("         ====================================\n")
print("\"You are in a storming blizzard! Find a way to survive\"\n")

#  Start State and Conditions
move = 1
wait = 0
count = 0
moveOne = "none"
moveTwo = "none"
moveThree = "none"
previous = "none"    # Track previous move for losing condition

while(True):
    #  Roundabout 3 Moves (WIN)
    if ((moveOne == "North" and moveTwo == "West" and moveThree == "South")
        or (moveOne == "North" and moveTwo == "East" and moveThree == "South")
        or (moveOne == "East" and moveTwo == "North" and moveThree == "West")
        or (moveOne == "East" and moveTwo == "South" and moveThree == "West")
        or (moveOne == "South" and moveTwo == "East" and moveThree == "North")
        or (moveOne == "South" and moveTwo == "West" and moveThree == "North")
        or (moveOne == "West" and moveTwo == "North" and moveThree == "East")
        or (moveOne == "West" and moveTwo == "South" and moveThree == "East")):
        print("\n>  You Persevered And Survived!")
        print("\"You Were Rescued Just In Time\"")
        print("EXITING GAME:   Thanks For Playing!\n")
        break
        
    #  Backtracked (LOSS)
    if move == 0:
        print("\n>  You Collaped And Unfortunately Did Not Survive ...")
        print("\"You Backtracked, Which Caused You To Get Lost\"")
        print("EXITING GAME:   Thanks For Playing!\n")
        break

    #  3 Moves Without Backtracking (WIN)
    if count == 3:
        print("\n>  You Persevered And Survived!")
        print("\"You Found Your Own Way Out\"")
        print("EXITING GAME:   Thanks For Playing!\n")
        break

    #  First Move
    if move == 1 and wait == 0:
        print(">  Move NORTH, EAST, SOUTH, or WEST ...")
        print("\"You are feeling tired:   you won't survive very long in this blizzard\"")
        wait = 1

    #  Second Move
    if move == 2 and wait == 0:
        print("\"You are feeling increasingly tired:   should you turn back?\"")
        wait = 1

    #  Third Move
    if move == 3 and wait == 0:
        print("\"You are absolutely exhasted:   maybe you should turn back?\"")
        wait = 1

    readIsGood, frame = vs.read()
    if(not readIsGood):
        continue

    #================#
    #  COLOR RANGES  #
    #================#

    #  HSV Color Model
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    #  Orange HSV Range (North)
    lOrange = np.array([0, 109, 195])
    uOrange = np.array([21, 255, 255])
    oMask = cv2.inRange(hsv, lOrange, uOrange)

    #  Yellow HSV Range (East)
    lYellow = np.array([35, 0, 215])
    uYellow = np.array([43, 171, 255])
    yMask = cv2.inRange(hsv, lYellow, uYellow)

    #  Green HSV Range (South)
    lGreen = np.array([63, 100, 197])
    uGreen = np.array([81, 255, 255])
    gMask = cv2.inRange(hsv, lGreen, uGreen)

    #  Blue HSV Range (West)
    lBlue = np.array([88, 98, 151])
    uBlue= np.array([110, 255, 255])
    bMask = cv2.inRange(hsv, lBlue, uBlue)

    #  Pink HSV Range (Quit)
    lPink = np.array([141, 141, 181])
    uPink = np.array([167, 255, 255])
    pMask = cv2.inRange(hsv, lPink, uPink)

    #=================#
    #  MARKER INPUTS  #
    #=================#

    #  ORANGE: North MARKER
    oContours, _ = cv2.findContours(oMask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    for orange in oContours:
        if cv2.contourArea(orange) <= 50:
            continue
        x, y, _, _ = cv2.boundingRect(orange)
        cv2.drawContours(frame, oContours, -1, (0, 128, 255), 3)  #  BGR

        #  If Orange Is Seen For 1.7 Seconds: Set Direction To NORTH
        if oCheck == 0:  #  First time check
            oLast = datetime.datetime.now()
            oCheck = 1  #  Set check for orange
        now = datetime.datetime.now()
        oDiff = now - oLast
        if oDiff.total_seconds() > 1.7:
            direction = "North"
    
    #  YELLOW: East Marker
    yContours, _ = cv2.findContours(yMask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    for yellow in yContours:
        if cv2.contourArea(yellow) <= 50:
            continue
        x, y, _, _ = cv2.boundingRect(yellow)
        cv2.drawContours(frame, yContours, -1, (0, 255, 255), 3)  #  BGR

        #  If Yellow Is Seen For 1.7 Seconds: Set Direction To EAST
        if yCheck == 0:  #  First time check
            yLast = datetime.datetime.now()
            yCheck = 1  #  Set check for yellow
        now = datetime.datetime.now()
        yDiff = now - yLast
        if yDiff.total_seconds() > 1.7:
            direction = "East"

    #  GREEN: South Marker
    gContours, _ = cv2.findContours(gMask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    for green in gContours:
        if cv2.contourArea(green) <= 50:
            continue
        x, y, _, _ = cv2.boundingRect(green)
        cv2.drawContours(frame, gContours, -1, (0, 255, 0), 3)  #  BGR

        #  If Green Is Seen For 1.7 Seconds: Set Direction To SOUTH
        if gCheck == 0:  #  First time check
            gLast = datetime.datetime.now()
            gCheck = 1  #  Set check for green
        now = datetime.datetime.now()
        gDiff = now - gLast
        if gDiff.total_seconds() > 1.7:
            direction = "South"

    #  BLUE: West Marker
    bContours, _ = cv2.findContours(bMask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    for blue in bContours:
        if cv2.contourArea(blue) <= 50:
            continue
        x, y, _, _ = cv2.boundingRect(blue)
        cv2.drawContours(frame, bContours, -1, (255, 128, 0), 3)  #  BGR

        #  If Blue Is Seen For 1.7 Seconds: Set Direction To WEST
        if bCheck == 0:  #  First time check
            bLast = datetime.datetime.now()
            bCheck = 1  #  Set check for blue
        now = datetime.datetime.now()
        bDiff = now - bLast
        if bDiff.total_seconds() > 1.7:
            direction = "West"

    #  Get Direction
    if direction != "none":
        print("You chose to travel:  ", direction)     # Direction precedence: West > South > East > North
        if move != 17:   #  Free roam not enabled
            count += 1   #  Increment move counter

        #  Move Cases
        if move == 1:
            moveOne = direction
            previous = direction
            move = 2  #  Change to move 2
            wait = 0
        elif move == 2:
            if direction == opposite(previous):  #  Check for backtrack
                move = 0  #  Backtracked (loss)
            else:
                moveTwo = direction
                previous = direction
                move = 3  #  Change to move 3
                wait = 0
        elif move == 3:
            if direction == opposite(previous):  #  Check for backtrack
                move = 0  #  backtracked (loss)
            else:
                moveThree = direction
        direction = "none"   # Reset direction for next input
    
    #  PINK: Quit Marker
    pContours, _ = cv2.findContours(pMask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    for pink in pContours:
        if cv2.contourArea(pink) <= 50:
            continue
        x, y, _, _ = cv2.boundingRect(pink)
        cv2.drawContours(frame, pContours, -1, (255, 0, 255), 3)  #  BGR

        #  If Pink Is Seen For 1.7 Seconds
        if pCheck == 0:  #  First time check
            pLast = datetime.datetime.now()
            pCheck = 1  #  Set check for pink
        now = datetime.datetime.now()
        pDiff = now - pLast
        if pDiff.total_seconds() > 1.7:
            pQuit = 1  #  Quit Flag Enabled

    #  Reset Input After 1.8 Seconds
    elapsed = datetime.datetime.now()
    reset = elapsed - last
    if reset.total_seconds() > 1.8:
        last = datetime.datetime.now()
        oCheck = 0        #  Reset check for orange
        yCheck = 0        #  Reset check for yellow
        gCheck = 0        #  Reset check for green
        bCheck = 0        #  Reset check for blue
        pCheck = 0        #  Reset check for pink
    
    #===========================#
    #  INTEGRATED CAMERA OUTPUT #
    #===========================#
    
    cv2.imshow("Storming Color", frame)
    key = cv2.waitKey(1)
    #  Free Roam Option
    if key == ord("f"):
        print("\n>  FREE ROAM ACTIVATED\n")
        move = 17  #  Free roam state
        count = 0
    elif key == ord("d"):
        if move == 17:
            print("\n>  FREE ROAM DEACTIVATED\n")
            move = 1  #  Reset to beginning of game
            wait = 0
        else:
            print("\n>  ERROR:   Free Roam Not Enabled\n")
    #  Closing The Game
    if key == ord("q"):   #  'Q' key pressed to close game (backup exit)
        break
    elif key == 27:       #  'Esc' key pressed to close game (backup exit)
        break
    elif pQuit == 1:      #  'Quit Marker' used to close game
        print("\n>  MANUAL GAME EXIT:   Thanks For Playing!\n")
        break
#  Cleanup The Camera And Close Any Open Windows
vs.release()
cv2.destroyAllWindows()