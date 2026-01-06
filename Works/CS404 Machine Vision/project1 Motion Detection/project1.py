# project1.py
#
# Miguel Villanueva
# October 18, 2020
#
# Program Description:
#   This program implements motion detection
#
# Modification (October 25, 2020)
#   Temporal filter method added through cv2.createBackgroundSubtractorMOG2()
#
# Sources:
#   https://www.pyimagesearch.com/2015/05/25/basic-motion-detection-and-tracking-with-python-and-opencv/
#   https://www.geeksforgeeks.org/webcam-motion-detector-python/
#   https://docs.opencv.org/3.4/d1/dc5/tutorial_background_subtraction.html

import os
import cv2
import numpy as np
import pickle

#  Change working directory to read calibration file
os.chdir("A:\MicrosoftVSCode\CS404\project1")

#  cv2.CAP_DSHOW used to avoid warning and provide better video quality
vs = cv2.VideoCapture(0, cv2.CAP_DSHOW)

#  Load calibration paramaters
calib = pickle.load(open("calib_params.p", "rb"))    #  "rb" for Read Binary

mtx = calib["mtx"]
dist = calib["dist"]

#  Initialize first frame
firstFrame = None

#  Create background subtraction object 
backSub = cv2.createBackgroundSubtractorMOG2()

while(True):
    readIsGood, frame = vs.read()

    #  Undistort
    h,  w = frame.shape[:2]
    newcameramtx, roi = cv2.getOptimalNewCameraMatrix(mtx,dist,(w,h),1,(w,h))
    dst = cv2.undistort(frame, mtx, dist, None, newcameramtx)
    x,y,w,h = roi
    dst = dst[y:y+h, x:x+w]

    #  Grayscale and smoothing
    gray = cv2.cvtColor(dst, cv2.COLOR_BGR2GRAY)
    blur = cv2.GaussianBlur(gray, (21, 21), 0)

    #  Check video capture read
    if(not readIsGood):
        continue

    #  Set first frame
    if firstFrame is None:
	    firstFrame = blur
	    continue

    #  Compute difference between first frame and current frame
    diff = cv2.absdiff(firstFrame, blur)

    #  Threshold, dilate, and find contours
    thresh = cv2.threshold(diff, 30, 255, cv2.THRESH_BINARY)[1]
    thresh = cv2.dilate(thresh, None, iterations = 2) 
    cnts,_ = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE) 

    #  Loop over contours
    for contour in cnts:
        #  Apply filter
        fgMask = backSub.apply(contour)
        #  If countour is smaller than specified area, ignore it
        if cv2.contourArea(contour) < 7500: 
            continue
        
        #  Compute bounding rectangle from contour and draw it on current frame
        (x, y, w, h) = cv2.boundingRect(contour)
        cv2.rectangle(dst, (x, y), (x + w, y + h), (0, 255, 0), 3) 

    #  Show video capture
    cv2.imshow("Video", dst)
    key = cv2.waitKey(1)
    if key == ord("q"):   #  'Q' key pressed to close image
        break
    elif key == 27:       #  'Esc' key pressed to close image
        break
#  Cleanup the camera and close any open windows
vs.release()
cv2.destroyAllWindows()
