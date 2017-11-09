from math import*
import time
import serial
import numpy as np
import matplotlib.pyplot as plt

index=[0]*8192
a=[0]*8192
signal=[0]*256
indices=[0]*256

for i in range(0,8192):
    index[i]=i-4096
for n in range(0,8192):
    #This is for sinc function
    if (index[n]*2*pi/4096)!=0:
        a[n]=int(((sin(index[n]*2*pi/1024))/(index[n]*2*pi/1024))*127+127)
    else:
        a[n]=255
    '''
     #This is for experession in t
    a[n]=int((index[n]*index[n])/(4096.0*4096.0)*127+127)
    '''
for n in range(0,256):
    signal[n]=a[n*32]
    indices[n]=index[32*n]
#print signal
plt.plot(indices,signal)
plt.show()


''' for periodic signal
Fs = 256
f = 1
sample = 256
indices = np.arange(sample)
signal = np.sin(2 * np.pi * f * x / Fs)*np.sin(2 * np.pi * f * x / Fs)
for n in range(sample):
    y[n]=int(y[n]*127+127)
plt.plot(x, y)
plt.xlabel('sample(n)')
plt.ylabel('voltage(V)')
plt.show()
print y

'''

ser =serial.Serial('COM7', 115200, timeout=1)
print(ser.name)
n=0
while 1:
    ser.write(chr(signal[n]))
    ser.write(chr(signal[n]))
    if(ser.read()=='S'):
        n=n+1
    if(n==256):
        break;
ser.close()
