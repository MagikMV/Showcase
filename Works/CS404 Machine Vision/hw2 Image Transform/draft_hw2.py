# hw2.py
#
# Miguel Villanueva
# September 11, 2020
#
# Program Description:
#

import cv2 as cv
#import numpy as np

img = cv.imread('img1.jpg', 1)
#print(type(img))
A = int(input("Please enter 'a': "))
#print("A is: ", A)
B = int(input("Please enter 'b': "))
#print("B is: ", B)
img = A * img + B

cv.namedWindow('image', cv.WINDOW_NORMAL)
cv.resizeWindow('image', 960,540)
cv.imshow('image', img)
cv.waitKey(0)
cv.destroyAllWindows()