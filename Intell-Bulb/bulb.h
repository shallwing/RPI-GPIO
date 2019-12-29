/********************************************************************************
 *      Copyright:  (C) 2019 SCUEC
 *                  All rights reserved.
 *
 *       Filename:  bulb.h
 *    Description:  This head file includes the basic declaration.
 *
 *        Version:  1.0.0(29/12/19)
 *         Author:  Donald Shallwing <donald_shallwing@foxmail.com>
 *      ChangeLog:  1, Release initial version on "29/12/19 13:17:19"
 *                 
 ********************************************************************************/
#ifndef _BULB_H
#define _BULB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <wiringPi.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <wiringPiI2C.h>
#include <signal.h>

#define BOUND					1.00
#define CONTROL_REG				0x80
#define SENOR_ADDR 				0x39
#define REG_COUNT				4
#define POWER_UP				0x03
#define POWER_DOWN				0x00
#define GPIO_RELAY              29      //This is the GPIO pin of the relay.
#define GPIO_INFRARED           28
#define SECOND                 	1 

enum									//Define the command control words.
{
		data0_low = 0x8c,
		data0_high,
		data1_low,
		data1_high,
};

double tsl2561();
void signal_handler(int signum);

#endif
