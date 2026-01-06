# hw3.py
#
# Miguel Villanueva
# September 27, 2020
#
# Program Description:
#   This program does Camera Calibration ...

import os
import cv2
import glob
import numpy as np
import pickle


os.chdir("A:\MicrosoftVSCode\CS404\hw3")

#  Termination criteria
criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)

#  Prepare object points, like (0,0,0), (1,0,0), (2,0,0) ....,(6,5,0)
objp = np.zeros((6*10,3), np.float32)
objp[:,:2] = np.mgrid[0:10,0:6].T.reshape(-1,2)

#  Arrays to store object points and image points from all the images.
objpoints = []  #  3d point in real world space
imgpoints = []  #  2d points in image plane.

vs = cv2.VideoCapture(0, cv2.CAP_DSHOW)

imgNum = 1    #  Used for file naming
while(True):
    readIsGood, frame = vs.read()
    if(not readIsGood):
        continue
    cv2.imshow("Video", frame)
    key = cv2.waitKey(1)
    if key == ord("q"):
        break
    elif key == 27:   #  ESC
        break
    elif key == 32:   #  Space
        fileName = "img{}.jpg".format(imgNum)
        cv2.imwrite(fileName, frame)
        imgNum += 1
#  Cleanup the camera and close any open windows
vs.release()
cv2.destroyAllWindows()

#  List of Calibration Images
images = glob.glob('*.jpg')

for fname in images:
    img = cv2.imread(fname)
    gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)

    #  Find the chess board corners
    ret, corners = cv2.findChessboardCorners(gray, (10,6),None)
    #ret, corners = cv2.findCirclesGrid(gray, (7,6), None)
    #ret, corners = cv2.findCirclesGrid(gray, (7,6), flags=cv2.CALIB_CB_ASYMMETRIC_GRID)
    #ret, corners = cv2.findCirclesGrid(gray, (16,6), flags=cv2.CALIB_CB_ASYMMETRIC_GRID + cv2.CALIB_CB_CLUSTERING)

    #  If found, add object points, image points (after refining them)
    if ret == True:
        objpoints.append(objp)

        corners2 = cv2.cornerSubPix(gray,corners,(11,11),(-1,-1),criteria)
        imgpoints.append(corners2)

        #  Draw and display the corners
        img = cv2.drawChessboardCorners(img, (10,6), corners2,ret)
        cv2.imshow('img',img)
        cv2.waitKey(0)

cv2.destroyAllWindows()

ret, mtx, dist, rvecs, tvecs = cv2.calibrateCamera(objpoints, imgpoints, gray.shape[::-1],None,None)
img = cv2.imread('img9.jpg')
h,  w = img.shape[:2]
newcameramtx, roi=cv2.getOptimalNewCameraMatrix(mtx,dist,(w,h),1,(w,h))

#  Undistort
dst = cv2.undistort(img, mtx, dist, None, newcameramtx)

#  Crop the image
x,y,w,h = roi
dst = dst[y:y+h, x:x+w]
cv2.imwrite('calibresult.png',dst)

#  Save the camera calibration results
dist_pickle = {}
dist_pickle["mtx"] = mtx
dist_pickle["dist"] = dist
pickle.dump(dist_pickle, open( "./undist_params.p", "wb" ))   #  "wb" for Write Binary
