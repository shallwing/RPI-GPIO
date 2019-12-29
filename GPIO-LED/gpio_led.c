#include <stdio.h>
#include <stdlib.h>
#include "gpio_led.h"
#include <wiringPi.h>

int main(void)
{
	struct sigaction		sigact;

	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = 0;
	sigact.sa_handler = signal_handler;

	sigaction(SIGINT, &sigact, 0);

	wiringPiSetup();

	init_led();

	light_led();

	return 0;
}
