# finalproject.py
#
# Miguel Villanueva
# November 30, 2020
#
# Program Description:
#   Text based adventure game using color tracking controls.
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

print("Time to grind brother man")

#  Function for null statement
def nothing(x):
    pass

#  cv2.CAP_DSHOW used to avoid warning and provide better video quality
vs = cv2.VideoCapture(0, cv2.CAP_DSHOW)

#  HSV Color Model
#cv2.namedWindow('Trackbars')
#cv2.createTrackbar('L - H', 'Trackbars', 0, 179, nothing)
#cv2.createTrackbar('L - S', 'Trackbars', 0, 255, nothing)
#cv2.createTrackbar('L - V', 'Trackbars', 0, 255, nothing)
#cv2.createTrackbar('U - H', 'Trackbars', 179, 179, nothing)
#cv2.createTrackbar('U - S', 'Trackbars', 255, 255, nothing)
#cv2.createTrackbar('U - V', 'Trackbars', 255, 255, nothing)

oCheck = 0
yCheck = 0
gCheck = 0
bCheck = 0
pCheck = 0
pQuit = 0
oLast = datetime.datetime.now()
yLast = datetime.datetime.now()
gLast = datetime.datetime.now()
bLast = datetime.datetime.now()
pLast = datetime.datetime.now()
elapsed = datetime.datetime.now()
last = datetime.datetime.now()
reset = elapsed - last

#Pog = 16
#print(Pog)
direction = "none"

while(True):
    readIsGood, frame = vs.read()
    if(not readIsGood):
        continue

    #  HSV Color Model
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    #  North
    lOrange = np.array([0, 109, 195])
    uOrange = np.array([21, 255, 255])
    oMask = cv2.inRange(hsv, lOrange, uOrange)

    #  East
    lYellow = np.array([35, 0, 215])
    uYellow = np.array([43, 171, 255])
    yMask = cv2.inRange(hsv, lYellow, uYellow)

    #  South
    lGreen = np.array([63, 100, 197])
    uGreen = np.array([81, 255, 255])
    gMask = cv2.inRange(hsv, lGreen, uGreen)

    #  West
    lBlue = np.array([88, 98, 151])
    uBlue= np.array([110, 255, 255])
    bMask = cv2.inRange(hsv, lBlue, uBlue)

    #  Quit
    lPink = np.array([141, 141, 181])
    uPink = np.array([167, 255, 255])
    pMask = cv2.inRange(hsv, lPink, uPink)

    #  North
    oContours, _ = cv2.findContours(oMask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    for orange in oContours:
        if cv2.contourArea(orange) <= 50:
            continue
        x, y, _, _ = cv2.boundingRect(orange)
        cv2.drawContours(frame, oContours, -1, (0, 128, 255), 3)
        if oCheck == 0:
            oLast = datetime.datetime.now()
            oCheck = 1
        now = datetime.datetime.now()
        oDiff = now - oLast
        if oDiff.total_seconds() > 1.7:
            direction = "North"
    
    #  East
    yContours, _ = cv2.findContours(yMask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    for yellow in yContours:
        if cv2.contourArea(yellow) <= 50:
            continue
        x, y, _, _ = cv2.boundingRect(yellow)
        cv2.drawContours(frame, yContours, -1, (0, 255, 255), 3)
        if yCheck == 0:
            yLast = datetime.datetime.now()
            yCheck = 1
        now = datetime.datetime.now()
        yDiff = now - yLast
        if yDiff.total_seconds() > 1.7:
            direction = "East"

    #  South
    gContours, _ = cv2.findContours(gMask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    for green in gContours:
        if cv2.contourArea(green) <= 50:
            continue
        x, y, _, _ = cv2.boundingRect(green)
        cv2.drawContours(frame, gContours, -1, (0, 255, 0), 3)
        if gCheck == 0:
            gLast = datetime.datetime.now()
            gCheck = 1
        now = datetime.datetime.now()
        gDiff = now - gLast
        if gDiff.total_seconds() > 1.7:
            direction = "South"

    #  West
    bContours, _ = cv2.findContours(bMask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    for blue in bContours:
        if cv2.contourArea(blue) <= 50:
            continue
        x, y, _, _ = cv2.boundingRect(blue)
        cv2.drawContours(frame, bContours, -1, (255, 128, 0), 3)
        if bCheck == 0:
            bLast = datetime.datetime.now()
            bCheck = 1
        now = datetime.datetime.now()
        bDiff = now - bLast
        if bDiff.total_seconds() > 1.7:
            direction = "West"
            #print("West")
            #Pog = 92
    #if Pog == 92:
        #print(Pog)
        #Pog = 16

    #  Get Direction
    if direction != "none":
        print(direction)     # Direction precedence: West > South > East > North
        direction = "none"
    
    #  Quit
    pContours, _ = cv2.findContours(pMask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    for pink in pContours:
        if cv2.contourArea(pink) <= 50:
            continue
        x, y, _, _ = cv2.boundingRect(pink)
        cv2.drawContours(frame, pContours, -1, (255, 0, 255), 3)  #  BGR
        if pCheck == 0:
            pLast = datetime.datetime.now()
            pCheck = 1
        now = datetime.datetime.now()
        pDiff = now - pLast
        if pDiff.total_seconds() > 1.7:
            pQuit = 1

    elapsed = datetime.datetime.now()
    reset = elapsed - last
    if reset.total_seconds() > 1.8:
        last = datetime.datetime.now()
        oCheck = 0
        yCheck = 0
        gCheck = 0
        bCheck = 0
        pCheck = 0
    
    #l_h = cv2.getTrackbarPos('L - H', 'Trackbars')
    #l_s = cv2.getTrackbarPos('L - S', 'Trackbars')
    #l_v = cv2.getTrackbarPos('L - V', 'Trackbars')
    #u_h = cv2.getTrackbarPos('U - H', 'Trackbars')
    #u_s = cv2.getTrackbarPos('U - S', 'Trackbars')
    #u_v = cv2.getTrackbarPos('U - V', 'Trackbars')
    #lower = np.array([l_h, l_s, l_v])
    #upper = np.array([u_h, u_s, u_v])
    #mask = cv2.inRange(hsv, lower, upper)
    #result = cv2.bitwise_and(frame, frame, mask = mask)

    cv2.imshow("Video", frame)
    #cv2.imshow('Mask', mask)q
    #cv2.imshow('Result', result)
    key = cv2.waitKey(1)
    if key == ord("q"):   #  'Q' key pressed to close game (backup)
        break
    elif key == 27:       #  'Esc' key pressed to close game (backup)
        break
    elif pQuit == 1:      #  'Quit Marker' used to close game
        print("\n>  MANUAL GAME EXIT:   Thanks For Playing!")
        break
#  Cleanup the camera and close any open windows
vs.release()
cv2.destroyAllWindows()