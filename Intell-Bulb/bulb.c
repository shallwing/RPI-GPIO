/*********************************************************************************
 *      Copyright:  (C) 2019 SCUEC
 *                  All rights reserved.
 *
 *       Filename:  bulb.c
 *    Description:  This src implements the intelligent light bulb. 
 *                 
 *        Version:  1.0.0(29/12/19)
 *         Author:  Donald Shallwing <donald_shallwing@foxmail.com>
 *      ChangeLog:  1, Release initial version on "29/12/19 13:25:55"
 *                 
 ********************************************************************************/

#include "bulb.h"

double tsl2561(){
	
	int reg_addr[REG_COUNT] = {data0_low, data0_high, data1_low, data1_high};
	
	int 				tsl_fd = -1;
	int 				chn_0 = 0, chn_1 = 0;
	int					i;
	int 				reg_data[REG_COUNT];
	double				div = 0, lux = -1.0; 
    
    tsl_fd = wiringPiI2CSetup(SENOR_ADDR);	       		//This funtion returns a fd for next reading step.
	if(tsl_fd < 0)
		goto end;
	
	wiringPiI2CWrite(tsl_fd, CONTROL_REG);
	wiringPiI2CWrite(tsl_fd, POWER_UP);

    sleep(SECOND);

	for(i = 0; i<REG_COUNT; i++){
		wiringPiI2CWrite(tsl_fd, reg_addr[i]);			//Write command control words.
		reg_data[i] = wiringPiI2CRead(tsl_fd);			//Read the data from the registers.
	}
	
	chn_0 = reg_data[1]*256 + reg_data[0];				//channel_0 = DATA0_HIGH*256 + DATA0_LOW;
	chn_1 = reg_data[3]*256 + reg_data[2];				//channel_1 = DATA1_HIGH*256 + DATA1_LOW;

	if(chn_0==0)
		goto end;
	if(chn_0<0 || chn_1<0)
		goto end;

	div = (double)chn_1 / (double)chn_0;

	if(div>0 && div<=0.5)
		lux = 0.304*chn_0-0.062*chn_0*pow(div,1.4);
    if(div>0.5 && div<=0.61)
    	lux = 0.0224*chn_0-0.031*chn_1;
    if(div>0.61 && div<=0.8)
    	lux = 0.0128*chn_0-0.0153*chn_1;
    if(div>0.8 && div<=1.3)
    	lux = 0.00146*chn_0-0.00112*chn_1;
    if(div>1.3)
    	lux = 0;

end:wiringPiI2CWrite(tsl_fd, CONTROL_REG);
	wiringPiI2CWrite(tsl_fd, POWER_DOWN);	
	return lux;
}

void signal_handler(int signum){
    if(signum==SIGINT || signum==SIGTERM || signum==SIGHUP || signum==SIGILL
	|| signum==SIGQUIT || signum==SIGABRT){
        digitalWrite(GPIO_RELAY, LOW);
        exit(0);
	}
}


int main(int argc, char **argv){
	
	wiringPiSetup();
    pinMode(GPIO_RELAY, OUTPUT);
    pinMode(GPIO_INFRARED, INPUT);
    
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    
    int 			state = -1;
    
    if(daemon(0,0) < 0){
    	printf("Fail to put the process into backstage: %s\n", strerror(errno));
    	return -1;
	}
    
    digitalWrite(GPIO_RELAY, LOW);
    
    while(1){
    	state = digitalRead(GPIO_INFRARED);
    	if(state>0 && tsl2561()<BOUND){
				digitalWrite(GPIO_RELAY, HIGH);
				sleep(10); 
				digitalWrite(GPIO_RELAY, LOW);
		}	
	}
}
