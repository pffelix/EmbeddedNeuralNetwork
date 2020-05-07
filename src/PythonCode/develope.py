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
count = 0

for folder in folderName:
    for i in os.listdir(folderPath + folder):           # iteration over all data files
        
        # get meta data
        deg = int(i[i.rfind("_")+1:i.find("degree")])/180*math.pi # read angle
        dist = 1 # read distance
        number = int(i[i.rfind("arctic")+7:i.find(str(math.ceil(fs/1000)) + "k")-1]) # read file number
        
        # read data file
        fs, data = wavfile.read(folderPath + folder + "/" + i)
        tempData = data
        audioCh1 = data[:,0]
        audioCh2 = data[:,1]
        
        # filter
        #sos = signal.butter(filterOrder, filterBand, 'bp', fs=fs, output='sos')
        #audioCh1 = signal.sosfilt(sos, audioCh1)
        #audioCh2 = signal.sosfilt(sos, audioCh2)
    
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