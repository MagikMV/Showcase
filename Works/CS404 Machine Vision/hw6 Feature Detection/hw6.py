# project1.py
#
# Miguel Villanueva
# November 15, 2020
#
# Program Description:
#   This program experiments with feature detection using keypoints and descriptors.
#
# [Self Note] New Programming Style Choice:
#   Decided to try captilizing step oriented comments. Maybe I'll keep doing it. Maybe not. 
#
# Sources:
#   https://docs.opencv.org/3.4/df/d54/tutorial_py_features_meaning.html
#   https://docs.opencv.org/3.4/db/d27/tutorial_py_table_of_contents_feature2d.html
#   https://docs.opencv.org/3.4/d1/d89/tutorial_py_orb.html
#   https://opencv-python-tutroals.readthedocs.io/en/latest/py_tutorials/py_feature2d/py_matcher/py_matcher.html
#   https://docs.opencv.org/master/d4/d5d/group__features2d__draw.html
#   https://docs.opencv.org/master/d0/d13/classcv_1_1Feature2D.html
#   https://docs.opencv.org/master/d3/d61/classcv_1_1KAZE.html

import os
import cv2
from matplotlib import pyplot as plt

#  Change Working Directory
os.chdir("A:\MicrosoftVSCode\CS404\hw6")

#  Choose Detector Method
detector = None

print("=====================================")
print(">  Please choose a detector method\n")
method = input("Enter 1 for ORB, Enter 2 for KAZE: ")

while(method != '1' and method != '2'):  #  Ensure 1 or 2
    method = input("Enter 1 for ORB, Enter 2 for KAZE: ")

if(method == '1'):
    detector = cv2.ORB_create()
elif(method == '2'):
    detector = cv2.KAZE_create()

#  Choose Input Image Set or Method Paramters
   #  not very useful for images that do not match
   #  thus it is a set of matching images
   #  set = {img1, img2}
print("\n>  Please choose an image set\n")
imgSet = input("Enter 1 for TLOU, Enter 2 for ITSV: ")

while(imgSet != '1' and imgSet != '2'):  #  Ensure 1 or 2
    imgSet = input("Enter 1 for TLOU, Enter 2 for ITSV: ")

if(imgSet == '1'):
    #  TLOU = The Last of Us
    img1 = cv2.imread('img1.jpg', cv2.IMREAD_GRAYSCALE)
    img2 = cv2.imread('img2.jpg', cv2.IMREAD_GRAYSCALE)
elif(imgSet == '2'):
    #  ITSV = Into The Spider-Verse
    img1 = cv2.imread('img3.jpg', cv2.IMREAD_GRAYSCALE)
    img2 = cv2.imread('img4.jpg', cv2.IMREAD_GRAYSCALE)
    
#  Find Keypoints and Descriptors with Chosen Detector
kp1, des1 = detector.detectAndCompute(img1, None)
kp2, des2 = detector.detectAndCompute(img2, None)

#  Create Brute Force Matcher Object
bf = cv2.BFMatcher()

#  Match Descriptors
matches = bf.match(des1, des2)

#  Sort Them in the Order of Their Distance
matches = sorted(matches, key = lambda x:x.distance)

# Draw First 25 Matches (Note: 25 is Arbitrary)
img3 = cv2.drawMatches(img1, kp1, img2, kp2, matches[:25], None, 
                       flags = cv2.DrawMatchesFlags_NOT_DRAW_SINGLE_POINTS)
print("\n>  Displaying matches ...\n")
plt.imshow(img3)
plt.show()