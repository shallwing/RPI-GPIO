#!/bin/bash

gcc init_led.c -c -lwiringPi;

gcc light_led.c -c -lwiringPi;

gcc signal_handler.c -c;

gcc gpio_led.c -o led -g -lwiringPi light_led.o init_led.o signal_handler.o;

rm *.o;

