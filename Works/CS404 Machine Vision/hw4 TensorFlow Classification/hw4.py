# hw4.py
#
# Miguel Villanueva
# October 4, 2020
#
# Program Description:
#   This program does basic classification
#
#   Source:
#     https://www.tensorflow.org/tutorials/keras/classification


#  Suppresses Tensorflow GPU messages
import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'

import tensorflow as tf
from tensorflow import keras

import numpy as np
import matplotlib.pyplot as plt

#  Import fashion MINST data set
fashion_mnist = keras.datasets.fashion_mnist
(train_images, train_labels), (test_images, test_labels) = fashion_mnist.load_data()
class_names = ['T-shirt/top', 'Trouser', 'Pullover', 'Dress', 'Coat',
                'Sandal', 'Shirt', 'Sneaker', 'Bag', 'Ankle boot']

#  Explore the data
print("\n") 
print(tf.__version__)        #  Tensorflow version
print(train_images.shape)    #  60,000, 28 x 28 pixel images (Training set)
print(len(train_labels))     #  60,000 labels in the training set
print(train_labels)          #  Labels are represented by an integer 0-9
print(test_images.shape)     #  10,000, 28 x 28 pixel images (Test set)
print(len(test_labels))      #  10,000 labels in the test set
print("\n") 

#  Preprocess the data
plt.figure()
plt.imshow(train_images[0])
plt.colorbar()
plt.grid(False)
plt.show()

#  Scale pixel values between 0 and 1 (previously from 0 to 255)
train_images = train_images / 255.0
test_images = test_images / 255.0

#  Verify data format by displaying first 25 images in the training set with class names
plt.figure(figsize = (10, 10))
for i in range(25):
    plt.subplot(5, 5, i + 1)
    plt.xticks([])
    plt.yticks([])
    plt.grid(False)
    plt.imshow(train_images[i], cmap=plt.cm.binary)
    plt.xlabel(class_names[train_labels[i]])
plt.show()

#  Set up the layers
model = keras.Sequential([
    keras.layers.Flatten(input_shape=(28, 28)),   #  Transform images from 2D to 1D
    keras.layers.Dense(128, activation='relu'),
    keras.layers.Dense(10)
])

#  Compile the model
model.compile(optimizer = 'adam',
              loss = tf.keras.losses.SparseCategoricalCrossentropy(from_logits = True),
              metrics = ['accuracy'])

#  Feed the model (start training)
model.fit(train_images, train_labels, epochs=10)

#  Evaluate the accuracy
test_loss, test_acc = model.evaluate(test_images,  test_labels, verbose=2)
print('\nTest accuracy:', test_acc)
print("\n")

#  Make predictions
probability_model = tf.keras.Sequential([model, tf.keras.layers.Softmax()])
predictions = probability_model.predict(test_images)   #  Label is predicted for each image (testing set)
print(predictions[0])                                  #  First prediction (an array of 10 numbers)
print(np.argmax(predictions[0]))                       #  Highest confidence value (ankle boot)
print(test_labels[0])                                  #  Classification is correct for ankle boot
print("\n")

#  Function for verifying predictions
def plot_image(i, predictions_array, true_label, img):

    true_label, img = true_label[i], img[i]
    plt.grid(False)
    plt.xticks([])
    plt.yticks([])

    plt.imshow(img, cmap = plt.cm.binary)

    predicted_label = np.argmax(predictions_array)
    if predicted_label == true_label:
        color = 'blue'
    else:
        color = 'red'

    plt.xlabel("{} {:2.0f}% ({})".format(class_names[predicted_label],
                                         100*np.max(predictions_array),
                                         class_names[true_label]),
                                         color = color)

#  Function for verifying predictions (cont.)
def plot_value_array(i, predictions_array, true_label):
    true_label = true_label[i]
    plt.grid(False)
    plt.xticks(range(10))
    plt.yticks([])
    thisplot = plt.bar(range(10), predictions_array, color = "#777777")
    plt.ylim([0, 1])
    predicted_label = np.argmax(predictions_array)

    thisplot[predicted_label].set_color('red')
    thisplot[true_label].set_color('blue')

#  Verification for the 0th image (correct = blue, incorrect = red)
i = 0
plt.figure(figsize=(6, 3))
plt.subplot(1, 2, 1)
plot_image(i, predictions[i], test_labels, test_images)
plt.subplot(1, 2, 2)
plot_value_array(i, predictions[i],  test_labels)
plt.show()

#  Verification for the 12th image (correct = blue, incorrect = red)
i = 12
plt.figure(figsize=(6,3))
plt.subplot(1,2,1)
plot_image(i, predictions[i], test_labels, test_images)
plt.subplot(1,2,2)
plot_value_array(i, predictions[i],  test_labels)
plt.show()

#  Verification for several images (correct = blue, incorrect = red)
num_rows = 5
num_cols = 3
num_images = num_rows*num_cols
plt.figure(figsize=(2*2*num_cols, 2*num_rows))
for i in range(num_images):
    plt.subplot(num_rows, 2*num_cols, 2*i+1)
    plot_image(i, predictions[i], test_labels, test_images)
    plt.subplot(num_rows, 2*num_cols, 2*i+2)
    plot_value_array(i, predictions[i], test_labels)
plt.tight_layout()
plt.show()

#  Use the trained model
img = test_images[1]            #  Image from test dataset
print(img.shape)                #  Image shape (28 x 28)
img = (np.expand_dims(img,0))   #  Add image to a batch where it's the only member

#  Predict correct label
predictions_single = probability_model.predict(img)
print(predictions_single)
plot_value_array(1, predictions_single[0], test_labels)
_ = plt.xticks(range(10), class_names, rotation=45)
plt.show()

#  Predicted label
print("\n")
print(np.argmax(predictions_single[0]))