# project2.py
#
# Miguel Villanueva
# November 27, 2020
#
# Program Description:
#
# Sources:
#   https://towardsdatascience.com/everything-you-need-to-know-about-neural-networks-and-backpropagation-machine-learning-made-easy-e5285bc2be3a
#   https://medium.com/tebs-lab/how-to-classify-mnist-digits-with-different-neural-network-architectures-39c75a0f03e3
#   https://towardsdatascience.com/image-classification-in-10-minutes-with-mnist-dataset-54c35b77a38d


#  Suppress Tensorflow GPU messages
import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'

import tensorflow as tf
from tensorflow import keras
from matplotlib import pyplot as plt
from tensorflow.keras.datasets import mnist
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Conv2D, Dropout, Flatten, MaxPooling2D

#  Change Working Directory
os.chdir("A:\MicrosoftVSCode\CS404\project2")

#(x_train, y_train), (x_test, y_test) = keras.datasets.mnist.load_data()
(x_train, y_train), (x_test, y_test) = mnist.load_data()


#  Flatten The Images
image_vector_size = 28*28
x_train = x_train.reshape(x_train.shape[0], image_vector_size)
x_test = x_test.reshape(x_test.shape[0], image_vector_size)

# Convert to "one-hot" vectors using the to_categorical function
num_classes = 10
y_train = keras.utils.to_categorical(y_train, num_classes)
y_test = keras.utils.to_categorical(y_test, num_classes)
#print("First 5 training lables as one-hot encoded vectors:\n", y_train[:5])

image_size = 784 # 28*28
num_classes = 10 # ten unique digits

#fcn_model = keras.models.Sequential()
fcn_model = Sequential()

# The input layer requires the special input_shape parameter which should match
# the shape of our training data.
fcn_model.add(Dense(units=5, activation='sigmoid', input_shape=(image_size,)))
fcn_model.add(Dense(units=num_classes, activation='softmax'))
#fcn_model.add(keras.layers.Dense(units=5, activation='sigmoid', input_shape=(image_size,)))
#fcn_model.add(keras.layers.Dense(units=num_classes, activation='softmax'))

fcn_model.compile(optimizer="sgd", loss='categorical_crossentropy', metrics=['accuracy'])
#history = fcn_model.fit(x_train, y_train, batch_size=128, epochs=5, verbose=False, validation_split=.1)
#fcn_model.fit(x_train, y_train, batch_size=128, epochs=10, verbose=False, validation_split=.1)
fcn_model.fit(x_train, y_train, batch_size=128, epochs=10)
loss, accuracy  = fcn_model.evaluate(x_test, y_test, verbose=False)

print(f'Test loss: {loss:.3}')
print(f'Test accuracy: {accuracy:.3}')

fcn_model.summary()

cnn_model = Sequential()
input_shape = (28, 28, 1)
cnn_model.add(Conv2D(28, kernel_size=(3,3), input_shape=input_shape))
cnn_model.add(MaxPooling2D(pool_size=(2, 2)))
cnn_model.add(Flatten()) # Flattening the 2D arrays for fully connected layers
cnn_model.add(Dense(128, activation=tf.nn.relu))
cnn_model.add(Dropout(0.2))
cnn_model.add(Dense(10,activation=tf.nn.softmax))

#image_index = 7777
#y_train1[image_index]
#print(y_train1[image_index])
#x_train1[image_index]
#x_train1 = x_train1.reshape(x_train1.shape[0], 28, 28, 1)
#x_train1 = x_train1.astype('float32')
#x_train1 /= 255
(x_train1, y_train1), (x_test1, y_test1) = keras.datasets.mnist.load_data()
x_train1 = x_train1.reshape(x_train1.shape[0], 28, 28, 1)
x_test1 = x_test1.reshape(x_test1.shape[0], 28, 28, 1)
x_train1 = x_train1.astype('float32')
x_test1 = x_test1.astype('float32')
x_train1 /= 255
x_test1 /= 255
cnn_model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])
cnn_model.fit(x=x_train1,y=y_train1, epochs=10)

loss1, accuracy1  = cnn_model.evaluate(x_test1, y_test1, verbose=False)
print(f'Test loss: {loss1:.3}')
print(f'Test accuracy: {accuracy1:.3}')

cnn_model.summary()