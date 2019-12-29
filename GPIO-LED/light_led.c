#include "gpio_led.h"

void light_led(void)
{
	int i;

	i = 0;

	while(1)
	{
		while(i<led_count)
		{
			digitalWrite(led_array[i], HIGH);

			usleep(SECOND/2);

			digitalWrite(led_array[i], LOW);

			i++;
		}
		i=0;

		{
			digitalWrite(led_array[0], HIGH);
			digitalWrite(led_array[1], HIGH);
			usleep(SECOND/2);
			digitalWrite(led_array[0], LOW);
			digitalWrite(led_array[1], LOW);
		}

		{

			digitalWrite(led_array[0], HIGH);
			digitalWrite(led_array[2], HIGH);
			usleep(SECOND/2);
			digitalWrite(led_array[0], LOW);
			digitalWrite(led_array[2], LOW);
		}

		{
			
			digitalWrite(led_array[1], HIGH);
			digitalWrite(led_array[2], HIGH);
			usleep(SECOND/2);
			digitalWrite(led_array[1], LOW);
			digitalWrite(led_array[2], LOW);
		}

		{

			digitalWrite(led_array[1], HIGH);
			digitalWrite(led_array[2], HIGH);
			digitalWrite(led_array[3], HIGH);
			usleep(SECOND/2);
			digitalWrite(led_array[1], LOW);
			digitalWrite(led_array[2], LOW);
			digitalWrite(led_array[3], LOW);
		}
		
	}

}
