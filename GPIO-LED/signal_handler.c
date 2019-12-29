#include "gpio_led.h"

void signal_handler(int signum)
{
	while(1)
	{
		if(signum == SIGINT)
		{
			digitalWrite(led_array[0], LOW);	
			digitalWrite(led_array[1], LOW);	
			digitalWrite(led_array[2], LOW);
			exit(0);
		}
	}	
}
