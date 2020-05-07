# Import the necessary packages
import os
import numpy as np
import math
from itertools import *
import more_itertools
from scipy import signal
from scipy.fftpack import fftshift
from scipy.io import wavfile
import matplotlib.pyplot as plt

from sklearn.model_selection import train_test_split
import tensorflow.keras as keras
from keras import layers, models
from keras import utils
from keras.layers import Dense, Dropout, Activation, Flatten, Conv2D, MaxPooling2D,BatchNormalization,GRU,Bidirectional,Reshape

fs = 16000;
windowIncrease = 0.1 #in sec
windowSize = 5 #in sec
filterOrder = 10
filterBand = [200,5000] #in Hertz
folderName = ["cmu_us_awb_arctic", "cmu_us_bdl_arctic", "cmu_us_clb_arctic", "cmu_us_jmk_arctic", "cmu_us_ksp_arctic", "cmu_us_rms_arctic", "cmu_us_slt_arctic"]
folderPath = "./../../../recording/speech/" + str(math.ceil(fs/1000)) + "khz" + "/"
#audioCh1Data = np.ndarray([0,windowSize*fs])
#audioCh2Data = np.ndarray([0,windowSize*fs])
#Y = np.ndarray([0,2])
audioCh1Data = []
audioCh2Data = []
Y = []

for folder in folderName:
    for i in os.listdir(folderPath + folder):           # iteration over all data files
        
        deg = int(i[i.rfind("_")+1:i.find("degree")])/180*math.pi # read angle
        dist = 1 # read distance
        number = int(i[i.rfind("arctic")+7:i.find(str(math.ceil(fs/1000)) + "k")-1]) # read file number
    
    
        fs, data = wavfile.read(folderPath + folder + "/" + i) # reading data file
    
        #l = int(np.size(data)/2)                  # split the two audio channels
        l = int(len(data))

    
        sos = signal.butter(filterOrder, filterBand, 'bp', fs=fs, output='sos')
        audioCh1Filtered = signal.sosfilt(sos, data[:,0])
        audioCh2Filtered = signal.sosfilt(sos, data[:,1])
    
        #l = int(np.size(audioCh1Filtered))
        l = int(len(audioCh1Filtered))
    
        #tempData = np.asarray(list(windowed(list(audioCh1Filtered), n=int(windowSize*fs), step=int(windowIncrease*fs))))
        #audioCh1Data = np.append(audioCh1Data,tempData[0:-1,:],axis=0)
    
        #tempData = np.asarray(list(windowed(list(audioCh2Filtered), n=int(windowSize*fs), step=int(windowIncrease*fs))))
        #audioCh2Data = np.append(audioCh2Data,tempData[0:-1,:],axis=0)
    
        #Y = np.append(Y,np.asarray(list(repeat([dist,deg],np.size(tempData[0:-1,0])))),axis=0)
    
        tempData = list(more_itertools.windowed(audioCh1Filtered, n=int(windowSize*fs), step=int(windowIncrease*fs)))
        tempData.pop()
        audioCh1Data.extend(tempData)
    
        tempData = list(more_itertools.windowed(audioCh2Filtered, n=int(windowSize*fs), step=int(windowIncrease*fs)))
        tempData.pop()
        audioCh2Data.extend(tempData)
    
        dataSize = (np.shape(tempData))[0]
        Y.extend(list(repeat([dist,deg],dataSize))) 
    
    
        print (np.shape(audioCh1Data),dist,deg)