#include "gpio_led.h"

void init_led(void)
{
	int i;

	for(i=0; i<led_count; i++)
	{
		pinMode(led_array[i], OUTPUT);
	}
} 
