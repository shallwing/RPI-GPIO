/**********************************************************************************
 *        Copyright:  (C) 2019 SCUEC
 *                    All rights reserved.
 * 
 *        Filename:  tsl2561.c
 *        Description:  This file is used for getting lux in tsl2561 senor.
 *                 
 *        Version:  1.0.0(04/03/19)
 *        Author:  Donald Shallwing <donald_shallwing@foxmail.com>
 *        ChangeLog:  1, Release initial version on "04/03/19 20:12:06"
 *             
 *********************************************************************************/

#include <wiringPi.h>
#include <wiringPiI2C.h>			//This must be included in I2C module while some manuals don't tell.
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <errno.h>

#define CONTROL_REG						0x80
#define SENOR_ADDR 						0x39
#define REG_COUNT						4
#define POWER_UP						0x03
#define POWER_DOWN						0x00

enum								//Define the command control words.
{
		data0_low = 0x8c,
		data0_high,
		data1_low,
		data1_high,
};								
int reg_addr[REG_COUNT] = {data0_low, data0_high, data1_low, data1_high};


int main(int argc, char **argv)
{
	int 				tsl_fd = -1;
	int 				i;
	int 				chn_0 = 0;
	int 				chn_1 = 0;
	int 				reg_data[REG_COUNT];
	double				div = 0;
	double 				lux = 0;
    
    tsl_fd = wiringPiI2CSetup(SENOR_ADDR);	       			//This funtion returns a fd for next reading step.
	if(tsl_fd < 0)
	{
		printf("Fail to read the relative i2c-dev file: %s", strerror(errno));
		return -1;
	}
	
	wiringPiI2CWrite(tsl_fd, CONTROL_REG);
	wiringPiI2CWrite(tsl_fd, POWER_UP);

    sleep(1);

	for(i = 0; i<REG_COUNT; i++)
	{
		wiringPiI2CWrite(tsl_fd, reg_addr[i]);			//Write command control words.
		reg_data[i] = wiringPiI2CRead(tsl_fd);			//Read the data from the registers.
	}
	
	chn_0 = reg_data[1]*256 + reg_data[0];				//channel_0 = DATA0_HIGH*256 + DATA0_LOW;
	chn_1 = reg_data[3]*256 + reg_data[2];				//channel_1 = DATA1_HIGH*256 + DATA1_LOW;

	if(chn_0==0)
	{
		lux = 0;
		goto end;
	}
	if(chn_0<0 || chn_1<0)
	{
		lux = 0;
		goto end;
	}

	div = (double)chn_1 / (double)chn_0;

	if(div>0 && div<=0.5)
	{
		lux = 0.304*chn_0-0.062*chn_0*pow(div,1.4);
    }
    if(div>0.5 && div<=0.61)
    {
    	lux = 0.0224*chn_0-0.031*chn_1;
    }
    if(div>0.61 && div<=0.8)
    {
    	lux = 0.0128*chn_0-0.0153*chn_1;
    }
    if(div>0.8 && div<=1.3)
    {
    	lux = 0.00146*chn_0-0.00112*chn_1;
    }
    if(div>1.3)
    {
    	lux = 0;
    }

end:	printf("%.3f\n", lux);
		
		wiringPiI2CWrite(tsl_fd, CONTROL_REG);
		wiringPiI2CWrite(tsl_fd, POWER_DOWN);
		
    	return 0;
}
