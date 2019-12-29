#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <wiringPi.h>

#define GPIO                   29               //This is the GPIO pin of the relay.
#define SECOND                 1 

void signal_handler(int signum);

int main(int argc, char **argv)
{
    wiringPiSetup();
    pinMode(GPIO, OUTPUT);

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    while(1)
    {
        digitalWrite(GPIO, HIGH);
        sleep(SECOND);
        digitalWrite(GPIO, LOW);
        sleep(SECOND);
    }
    
    
    return 0;
}

void signal_handler(int signum)
{
    if(signum == SIGINT)
    {
        digitalWrite(GPIO, LOW);
        exit(0);
    }
    if(signum == SIGTERM)
    {
        digitalWrite(GPIO, LOW);
        exit(0);
    }
}
