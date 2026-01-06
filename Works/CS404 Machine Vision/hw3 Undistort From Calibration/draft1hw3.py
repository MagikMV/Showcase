# hw3.py
#
# Miguel Villanueva
# September 27, 2020
#
# Program Description:
#   This program does Camera Calibration ...

import cv2
import glob
import numpy as np
import os

print("Current Working Directory: ", os.getcwd())
os.chdir("A:\MicrosoftVSCode\CS404\hw3")
print("Current Working Directory: ", os.getcwd())

#  Termination criteria
criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)

#  Prepare object points, like (0,0,0), (1,0,0), (2,0,0) ....,(6,5,0)
objp = np.zeros((6*7,3), np.float32)
objp[:,:2] = np.mgrid[0:7,0:6].T.reshape(-1,2)

#  Arrays to store object points and image points from all the images.
objpoints = []  #  3d point in real world space
imgpoints = []  #  2d points in image plane.

vs = cv2.VideoCapture(0, cv2.CAP_DSHOW)

while(True):
    readIsGood, frame = vs.read()
    if(not readIsGood):
        continue
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    ret, corners = cv2.findChessboardCorners(gray, (7,6),None)
    #ret, corners = cv2.findCirclesGrid(gray, (7,6),None)

images = glob.glob('*.jpg')

for fname in images:
    #  If found, add object points, image points (after refining them)
    if ret == True:
        objpoints.append(objp)
        corners2 = cv2.cornerSubPix(gray, corners,(11,11), (-1,-1), criteria)
        imgpoints.append(corners2)

        cv2.drawChessboardCorners(gray, (7,6), corners2, ret)
        print("Code is working PogU")

        cv2.imshow('Find Chessboard', gray)
        cv2.waitKey(0)

    #cv.imshow("Video", frame)
    cv2.imshow("Video", gray)
    key = cv2.waitKey(1) & 0xFF

    #  If 'q' key is pressed, break from the loop
    if key == ord("q"):
        break

#  Cleanup the camera and close any open windows
vs.release()
cv2.destroyAllWindows()