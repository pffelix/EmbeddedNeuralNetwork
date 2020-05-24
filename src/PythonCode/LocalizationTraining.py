#!/usr/bin/env python
# coding: utf-8

# In[1]:


# Import the necessary packages
import os
import numpy as np
import numpy.matlib
import math
from itertools import *
import more_itertools
from scipy import signal
from scipy.fftpack import fftshift
from scipy.io import wavfile
import matplotlib.pyplot as plt
import pyfftw
import simplespectral
 
from sklearn.model_selection import train_test_split
import tensorflow.keras as keras
from tensorflow.keras import layers, models
from tensorflow.keras import utils
from tensorflow.keras.layers import Dense, Dropout, Activation, Flatten, Conv2D, MaxPooling2D,BatchNormalization,GRU,Bidirectional,Reshape


# In[2]:


# parameters
user = "Parham"
fs = 16000;
filesN = 1132;
angleN = 8;
micN= 2;
windowIncrease = 0.1 #in sec
windowSize = 5 #in sec
filterOrder = 10
filterBand = [200,5000] #in Hertz
fftWindowN = 257 # singlesided
featureType = "magnitude"
speakerType = ["cmu_us_bdl_arctic"]#, "cmu_us_bdl_arctic", "cmu_us_clb_arctic", "cmu_us_jmk_arctic"] # , "cmu_us_ksp_arctic", "cmu_us_rms_arctic", "cmu_us_slt_arctic"
speakerTypeN = 1
if user == "Felix":
    folderPath = "./../../../../Shared/SoundLocalization/speech_database/" + str(math.ceil(fs/1000)) + "khz" + "/"
else:
    folderPath = "./../Polybox/SoundLocalization/speech_database/" + str(math.ceil(fs/1000)) + "khz"
#audioCh1Data = np.ndarray([0,windowSize*fs])
#audioCh2Data = np.ndarray([0,windowSize*fs])
readBatchOn = True;
filterOn = False;


# In[3]:


# read in data

# init
audioCh1Data = []
audioCh2Data = []
Y = []
count = 0
folderN = len(speakerType)
if fs == 16000:
    if featureType == "raw":
        samplesN = 113599;
        data = np.zeros((samplesN, angleN, filesN, micN, speakerTypeN), dtype = np.int16)
    if featureType == "magnitude":
        samplesN = 113851;
        fftWindowT = int(samplesN / fftWindowN);
        data = np.zeros((speakerTypeN,filesN, angleN, fftWindowT, fftWindowN, micN), dtype = np.int16) # fftWindowN, fftWindowT, angleN, filesN, speakerTypeN, micN

# read data
for folder_i in range(speakerTypeN):
    if readBatchOn:

        # read data file
        print ("read data file")
        fs, data_i = wavfile.read(folderPath + "/" + speakerType[folder_i] + "_" + featureType + ".wav")
        print ("finish load data file")
        print (np.shape(data_i))
        
        # 
        if filterOn:
            sos = signal.butter(filterOrder, filterBand, 'bp', fs=fs, output='sos')
            data_i[:,0] = signal.sosfilt(sos, data_i[:,0])
            data_i[:,1] = signal.sosfilt(sos, data_i[:,1])
            
        # reshape into invidual databases
        if featureType == "raw":
            data_i = np.reshape(data_i, (samplesN, angleN, filesN, micN))
        if featureType == "magnitude":            
            data_i = np.reshape(data_i, (filesN, angleN, fftWindowT, fftWindowN, micN))
            print (np.shape(data_i))
            
        # merge into one database
        data[folder_i,:,:,:,:,:] = data_i
        
        print("data reshaped")
        print(np.shape(data))
        
    else:
        for i in os.listdir(folderPath + folder):           # iteration over all single data files
            
            # get meta data
            deg = int(i[i.rfind("_")+1:i.find("degree")])/180*math.pi # read angle
            dist = 1 # read distance
            number = int(i[i.rfind("arctic")+7:i.find(str(math.ceil(fs/1000)) + "k")-1]) # read file number
            
            # read data file
            tempData = data
            audioCh1 = data[:,0]
            audioCh2 = data[:,1]
            
            # filter
            if filterOn:
                sos = signal.butter(filterOrder, filterBand, 'bp', fs=fs, output='sos')
                audioCh1 = signal.sosfilt(sos, audioCh1)
                audioCh2 = signal.sosfilt(sos, audioCh2)
        
            # window (rectangular)
            tempData = list(more_itertools.windowed(audioCh1, n=int(windowSize*fs), step=int(windowIncrease*fs)))
            tempData.pop()
            audioCh1Data.extend(tempData)
        
            tempData = list(more_itertools.windowed(audioCh2, n=int(windowSize*fs), step=int(windowIncrease*fs)))
            tempData.pop()
            audioCh2Data.extend(tempData)
        
            # resphape into one array
            dataSize = (np.shape(tempData))[0]
            Y.extend(list(np.repeat([dist,deg],dataSize))) 
        
            # log
            print (i)
            
print ("finished all data files' load")


# In[4]:


# calculate features
                        # speaker, file number, angle, time bins, frequency bins, channel
data = np.moveaxis (data,[0,1,2,3,4,5],[0,1,2,4,3,5])
# show dimensions
print (np.shape(data)) # speaker, file number, angle, frequency bins, time bins, channel

# visualize features
plt.figure(figsize=(12, 8))
plt.subplot (221)
t = np.linspace(1,fftWindowT, fftWindowT)
f = np.linspace(1,fftWindowN, fftWindowN)
plot_data = data[0,1131,0,:,:,0] # :,:,0,0,0,0
plot_data = plot_data / np.amax(np.amax(plot_data))
plt.pcolormesh(t, f, plot_data)
plt.ylabel('Frequency [Hz]')
plt.xlabel('Time [sec]')
plt.subplot (222)
t = np.linspace(1,fftWindowT, fftWindowT)
f = np.linspace(1,fftWindowN, fftWindowN)
plot_data = data[0,1131,0,:,:,1] # :,:,0,0,0,0
plot_data = plot_data / np.amax(np.amax(plot_data))
plt.pcolormesh(t, f, plot_data)
plt.ylabel('Frequency [Hz]')
plt.xlabel('Time [sec]')

# prepare features for neural network
X = np.reshape(data, (angleN * filesN * speakerTypeN, fftWindowT, fftWindowN, micN))

# get meta data
deg = np.linspace(0, 315, angleN)
deg = np.matlib.repmat(deg, 1, filesN  * speakerTypeN).transpose()
#dist = np.full((filesN * angleN * speakerTypeN, 1), 1)

# prepare lables for neural network
#Y = np.vstack((deg.T, dist.T)).T
Y = deg#/360
print (np.shape(Y)) # speaker-angle-file number, angle, distance
print (np.shape(X)) # speaker-angle-file number, time bins, frequency bins, channel


# In[5]:


X_train, X_validate, Y_train, Y_validate = train_test_split(X, Y, test_size = 0.2, random_state = 2)
print (np.shape(X_train))
print (np.shape(X_validate))
print (np.shape(Y_train))
print (np.shape(Y_validate))

X_train = X_train.astype('float16')
X_validate = X_validate.astype('float16')
Y_train = Y_train.astype('float16')
Y_validate = Y_validate.astype('float16')


# In[ ]:


# Define batchsize and number of epochs
batchSize = 200
nEpochs = 20


# Declare the sequential model and design your multi-layer perceptron
model = models.Sequential()

model.add(Conv2D(8, (3, 3), padding='same',
                 input_shape=X_train.shape[1:]))
model.add(Activation('relu'))
model.add(BatchNormalization())
model.add(MaxPooling2D(pool_size=(2, 2)))

model.add(Conv2D(16, (3, 3), padding='same'))
model.add(Activation('relu'))
model.add(BatchNormalization())
model.add(MaxPooling2D(pool_size=(2, 2)))

model.add(Conv2D(32, (3, 3), padding='same'))
model.add(Activation('relu'))
model.add(BatchNormalization())
model.add(MaxPooling2D(pool_size=(2, 2)))


# model.add(Conv2D(64, (3, 3), padding='same'))
# model.add(Activation('relu'))
# model.add(BatchNormalization())
# model.add(MaxPooling2D(pool_size=(2, 2)))

# model.add(Conv2D(128, (3, 3), padding='same'))
# model.add(Activation('relu'))
# model.add(BatchNormalization())
# model.add(MaxPooling2D(pool_size=(2, 2)))

model.add(Reshape((32,1760)))
model.add(Bidirectional(GRU(64)))

#model.add(Bidirectional(GRU(64)))

#model.add(Flatten())
model.add(Dense(256))
model.add(Activation('linear'))
model.add(Dense(64))
model.add(Activation('linear'))
model.add(Dense(1))
#model.add(Activation('sigmoid'))

# Compile your model
model.compile(loss='mean_absolute_error',
              optimizer='sgd',
              metrics=['mae','mse'])


# Train your model
model.fit(X_train, Y_train, epochs = nEpochs , batch_size = batchSize)


# In[ ]:


model.build()
model.summary ()


# In[ ]:


Y_validateChange = np.zeros (np.shape(Y_validate),dtype=np.float16)
for i in range(len(Y_validate)):
    if (Y_validate[i] == 0):
        Y_validateChange[i] = 25
    if (Y_validate[i] == 45):
        Y_validateChange[i] = 85
    if (Y_validate[i] == 90):
        Y_validateChange[i] = 135
    if (Y_validate[i] == 135):
        Y_validateChange[i] = 195
    if (Y_validate[i] == 180):
        Y_validateChange[i] = 260
    if (Y_validate[i] == 225):
        Y_validateChange[i] = 315
    if (Y_validate[i] == 270):
        Y_validateChange[i] = 370
    if (Y_validate[i] == 315):
        Y_validateChange[i] = 420
model.evaluate (X_validate,Y_validate)


# In[ ]:


Y_pred = model.predict (X_validate)
index = 0
plt.plot (Y_pred,'bs',Y_validateChange,'g^')
plt.show()


# In[ ]:


model.save ('angleGood.h5')


# In[ ]:


model = models.load_model('angelGood.h5')


# In[ ]:




