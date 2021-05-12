#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

#define GPIO_INFRARED           28

void sig_handler(int signum);

int main(int argc, char **argv)
{
	int 								state = -1;
	
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGTERM, sig_handler);
	signal(SIGABRT, sig_handler);
	
    wiringPiSetup();

    pinMode(GPIO_INFRARED, INPUT);
    
    while(1)
	{
		state = digitalRead(GPIO_INFRARED);
		if(state==-1)
		{
			printf("Something wrong in the infrared, process abort!\n");
			return -1;
		}
		if(state)
			printf("Someone is comming!\n");
		else
			printf("Noboby near here\n");

        sleep(1);
	}
	
	return 0;
}


void sig_handler(int signum)
{
	switch(signum)
	{
		case SIGINT:
			printf("Catch signal SIGINT, process exit\n");
			exit(1);
		case SIGQUIT:
			printf("Catch signal SIGQUIT, process exit\n");
			exit(1);
		case SIGABRT:	
			printf("Catch signal SIGINT, process exit\n");
			exit(1);
		case SIGTERM:
			printf("Catch signal SIGTERM, process exit\n");
			exit(1);
	}
}
