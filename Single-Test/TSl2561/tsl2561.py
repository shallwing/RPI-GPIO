#!/usr/bin/python

import wiringpi as wpi
import time

TSL2561_ADDR			= 0x39
POWER_UP          		= 0x03
POWER_DOWN        		= 0x00
CONTROL_REG       		= 0x80
DATA0_LOW				= 0x8c
DATA0_HIGH			  	= 0x8d
DATA1_LOW				= 0x8e
DATA1_HIGH				= 0x8f


##Register initialization
tsl_fd = wpi.wiringPiI2CSetup(TSL2561_ADDR)


wpi.wiringPiI2CWrite(tsl_fd, CONTROL_REG)
wpi.wiringPiI2CWrite(tsl_fd, POWER_UP)

time.sleep(0.5)

##Read the values from Ch,Dh,Eh,Fh
wpi.wiringPiI2CWrite(tsl_fd, DATA0_LOW)
data0_low = wpi.wiringPiI2CRead(tsl_fd)

wpi.wiringPiI2CWrite(tsl_fd, DATA0_HIGH)
data0_high = wpi.wiringPiI2CRead(tsl_fd)

wpi.wiringPiI2CWrite(tsl_fd, DATA1_LOW)
data1_low = wpi.wiringPiI2CRead(tsl_fd)

wpi.wiringPiI2CWrite(tsl_fd, DATA1_HIGH)
data1_high = wpi.wiringPiI2CRead(tsl_fd)


##Convert the register values into sampling values(channel_0 & channel_1)
chn0=256*data0_high+data0_low
chn1=256*data1_high+data1_low


##According to the 'div', calculate the size of lux
if chn0==0:
    lux = 0
elif chn0!=0:
        div=float(chn1)/float(chn0)
        if (div>0 and div<=0.5):
            lux =  (0.304*chn0-0.062*chn0*(div**1.4))
        if (div>0.5 and div<=0.61):
			lux = (0.0224*chn0-0.031*chn1)
        if (div>0.61 and div<=0.8):
			lux = (0.0128*chn0-0.0153*chn1)
        if (div>0.8 and div<=1.3):
			lux = (0.00146*chn0-0.00112*chn1)
        if (div >1.3):
            lux = 0


##Display the Lux
print '%.3f' % lux

##End of sampling
wpi.wiringPiI2CWrite(tsl_fd, CONTROL_REG)
wpi.wiringPiI2CWrite(tsl_fd, POWER_DOWN)