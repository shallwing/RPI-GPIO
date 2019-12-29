#ifndef _GPIO_LED_H
#define _GPIO_LED_H

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>

#define SECOND				1000*1000

enum 
{
	led_read = 0,

	led_green,	
	
	led_blue,

	led_count,
};
static int led_array[led_count] = { 27, 28, 29 };

void init_led(void);
void light_led(void);
void signal_handler(int signum);

#endif
