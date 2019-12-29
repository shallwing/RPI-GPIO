#!/usr/bin/env
#encoding: utf-8

import RPi.GPIO
import time

G,R,B=16,20,21

RPi.GPIO.setmode(RPi.GPIO.BCM)
RPi.GPIO.setup(R, RPi.GPIO.OUT)
RPi.GPIO.setup(G, RPi.GPIO.OUT)
RPi.GPIO.setup(B, RPi.GPIO.OUT)

try:
	t = 1
	while True:
		RPi.GPIO.output(R, RPi.GPIO.HIGH)
		time.sleep(t)
		RPi.GPIO.output(R, RPi.GPIO.LOW)

		RPi.GPIO.output(G, RPi.GPIO.HIGH)
		time.sleep(t)
		RPi.GPIO.output(G, RPi.GPIO.LOW)

		RPi.GPIO.output(B, RPi.GPIO.HIGH)
		time.sleep(t)
		RPi.GPIO.output(B, RPi.GPIO.LOW)

except KeyboardInterrupti:
	pass
RPi.GPIO.cleanup()
	
