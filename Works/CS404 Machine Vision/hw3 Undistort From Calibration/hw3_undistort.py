# hw3_undistort.py
#
# Miguel Villanueva
# September 27, 2020
#
# Program Description:
#   This program loads the saved calibration from hw3_calibrate.py to
#   undistort an arbitrary image from the camera.
#
#   Sources:
#     https://www.youtube.com/watch?v=2Tw39kZIbhs&t=395s
#     https://www.youtube.com/watch?v=Pl4Hp8qwwes
#     https://www.youtube.com/watch?v=WP2K7MHWz6U
#     https://www.youtube.com/watch?v=6wSFWOleZlc
#     https://docs.python.org/2/library/pickle.html

import os
import cv2
import numpy as np
import pickle

#  Change working directory to read and write images
os.chdir("A:\MicrosoftVSCode\CS404\hw3")

#  cv2.CAP_DSHOW used to avoid warning and provide better video quality
vs = cv2.VideoCapture(0, cv2.CAP_DSHOW)

while(True):
    readIsGood, frame = vs.read()
    if(not readIsGood):
        continue
    cv2.imshow("Video", frame)
    key = cv2.waitKey(1)
    if key == ord("q"):   #  'Q' key pressed to close image
        break
    elif key == 27:       #  'Esc' key pressed to close image
        break
    elif key == 32:       #  'Space' key pressed to save image
        cv2.imwrite('in.jpg', frame)
#  Cleanup the camera and close any open windows
vs.release()
cv2.destroyAllWindows()

#  Load calibration paramaters
calib = pickle.load(open("calib_params.p", "rb"))    #  "rb" for Read Binary

mtx = calib["mtx"]
dist = calib["dist"]

#  Undistort
img = cv2.imread('in.jpg')
h,  w = img.shape[:2]
newcameramtx, roi=cv2.getOptimalNewCameraMatrix(mtx,dist,(w,h),1,(w,h))
dst = cv2.undistort(img, mtx, dist, None, newcameramtx)

#  Crop the image
x,y,w,h = roi
dst = dst[y:y+h, x:x+w]
cv2.imwrite('out.jpg',dst)