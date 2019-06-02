#!/usr/bin/python
#-*- coding:utf-8 -*-   

'''Trains a simple convnet on the MNIST dataset.
Gets to 99.25% test accuracy after 12 epochs
(there is still a lot of margin for parameter tuning).
16 seconds per epoch on a GRID K520 GPU.
'''

from __future__ import print_function
import keras
from keras.datasets import mnist
from keras.models import Sequential
from keras.layers import Dense, Dropout, Flatten, Activation
from keras.layers import Conv2D, MaxPooling2D,Convolution2D
from keras import backend as K
from keras.optimizers import SGD

from cvhelp import *
from FileUtil import *

batch_size = 128    
epochs = 12
# input image dimensions
img_rows, img_cols = 128, 128
img_channel = 3

class Vgg:

    #获取待训练图片列表及其解
    def loadImage(self, path):
        imgs = []
        cvHelp = CvHelp()
        fileUtil = FileUtil()
        (files, counts, dirs) = fileUtil.getSamplesLabelsDirnames(path)
        for file in files :
            img = cv2.resize(cvHelp.open(file), (img_rows, img_cols))
            imgs.append(img)
        imgs = np.array(imgs)   
        counts = np.array(counts)
        counts -= counts.min()
        dirs = np.array(dirs)
        return imgs, counts, dirs   
    #加工图片结构
    def makeData(self, path):
        # the data, shuffled and split between train and test sets
        # 数据结构
        # (60000, 28, 28)   (60000, ) (10000, 28, 28)   (10000, )
        #(x_train,           y_train), (x_test,          y_test  ) = mnist.load_data()
        x_train, y_train, dirs = self.loadImage(path)
        num_classes = dirs.shape[0] #解空间 y 二进制转换位数设置 <- y最大数值
     
        if K.image_data_format() == 'channels_first':
            x_train = x_train.reshape(x_train.shape[0], img_channel, img_rows, img_cols)  # (60000, 1, 28, 28)
            input_shape = (img_channel, img_rows, img_cols)
        else:
            x_train = x_train.reshape(x_train.shape[0], img_rows, img_cols, img_channel)  # (60000, 28, 28, 1)
            input_shape = (img_rows, img_cols, img_channel)

        x_train = x_train.astype('float32')     
        x_train /= 255                          #(11221, 12, 13, 1) = 0/1

        # convert class vectors to binary class matrices
        y_train = keras.utils.to_categorical(y_train, num_classes)   # (0, 0, 0, 0, 0, 1, 0, 0...)
        print(x_train.shape)
        print(y_train.shape)
        print(num_classes)
        print(input_shape)
        return x_train,y_train,num_classes,input_shape, dirs
    def makeModel(self, x_train,y_train,num_classes,input_shape):
        model = Sequential()
        # input: 100x100 images with 3 channels -> (3, 100, 100) tensors.
        # this applies 32 convolution filters of size 3x3 each.
        model.add(Convolution2D(32, 3, 3, border_mode='valid', input_shape=input_shape))
        model.add(Activation('relu'))
        model.add(Convolution2D(32, 3, 3))
        model.add(Activation('relu'))
        model.add(MaxPooling2D(pool_size=(2, 2)))
        model.add(Dropout(0.25))

        model.add(Convolution2D(64, 3, 3, border_mode='valid'))
        model.add(Activation('relu'))
        model.add(Convolution2D(64, 3, 3))
        model.add(Activation('relu'))
        model.add(MaxPooling2D(pool_size=(2, 2)))
        model.add(Dropout(0.25))

        model.add(Flatten())
        # Note: Keras does automatic shape inference.
        model.add(Dense(256))
        model.add(Activation('relu'))
        model.add(Dropout(0.5))

        model.add(Dense(num_classes))#几个分类就要有几个dense
        model.add(Activation('softmax'))

        #sgd = SGD(lr=0.1, decay=1e-6, momentum=0.9, nesterov=True)
        # model.compile(loss='categorical_crossentropy', optimizer=sgd)
        # 多分类
        model.compile(loss='categorical_crossentropy',                                 # matt，多分类，不是binary_crossentropy
                      optimizer='rmsprop',
                      metrics=['accuracy'])
        # 优化器rmsprop：除学习率可调整外，建议保持优化器的其他默认参数不变
        
        model.fit(x_train, y_train, batch_size=32, epochs=16)
        model.add(Dense(num_classes))
        model.add(Activation('softmax'))

        sgd = SGD(lr=0.1, decay=1e-6, momentum=0.9, nesterov=True)
        model.compile(loss='categorical_crossentropy', optimizer=sgd)

        model.fit(x_train, y_train, batch_size=32, epochs=4)
        return model
    def testModel(self):

        x_train,y_train,num_classes,input_shape,dirs = self.makeData("ns")
       

        model = self.makeModel(x_train,y_train,num_classes,input_shape)

        # score = model.evaluate(x_test, y_test, verbose=0)
        # print('Test loss:', score[0])
        # print('Test accuracy:', score[1])
    def predict(self, model, ifshow=False):

        for i in range(11):
            x, y,num_classes,input_shape, dirs = self.makeData("ns/"+str(i))
            if(ifshow):
                mp = model.predict(x, batch_size=batch_size)
                print(mp)
            mpc = model.predict_classes(x, batch_size=batch_size)
            print(mpc)

if __name__ == '__main__':
    vgg = Vgg()
    vgg.testModel()
