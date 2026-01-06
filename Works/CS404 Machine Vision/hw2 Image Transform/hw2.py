# hw2.py
#
# Miguel Villanueva
# September 11, 2020
#
# Program Description:
#   The following attempts to answer Question 3 in Chapter 2 of
#   Fundamentals of Computer Vision (2017). Moreover, this program
#   takes an image in, and outputs it using:  g(x) = αf(x) + β .
#
#   -  1) User input is taken for α & β .
#   -  2) The image is transformed.
#   -  3) The image is displayed. 
#   -  4) User is asked if they would like to save the output.


import cv2 as cv
import os

print("Current Working Directory: ", os.getcwd())
os.chdir("A:\MicrosoftVSCode\CS404\hw2")
print("Current Working Directory: ", os.getcwd())

#  Read image
#img = cv.imread('img.jpg', 1)                      #  Issue is here
#img = cv.imread('A:\img.jpg', cv.IMREAD_COLOR)     #  Fixed
img = cv.imread('img.jpg', cv.IMREAD_COLOR)         #  Ultra fixed with os.chdir

#  Ensure A is an integer
checkA = input("Please enter an integer for α: ")
if not checkA.isdigit():
    while(checkA.isdigit() == False):
        checkA = input("Please enter an integer for α: ")
A = int(checkA)

#  Ensure B is an integer
checkB = input("Please enter an integer for β: ")
if not checkB.isdigit():
    while(checkB.isdigit() == False):
        checkB = input("Please enter an integer for β: ")
B = int(checkB)

#  Transform image
img = A * img + B

#  Display image
print("\n>  Displaying image ...\n")
cv.namedWindow('image', cv.WINDOW_NORMAL)
cv.resizeWindow('image', 960,540)
cv.imshow('image', img)
cv.waitKey(0)
cv.destroyAllWindows()

#  Write image
print("If you would like to save the image type 'Y'")
print("[WARNING] This will overwite an existing save: 'out.jpg'")
save = input("Y/N:  ")
if save == "Y":
    cv.imwrite('out.jpg', img)
    print("\n>  File successfully saved! Have a great day!")
else:
    print("\n>  Have a great day!")
    print("\n[IMPORTANT] If you meant to save, you must type exactly the letter 'Y'.")