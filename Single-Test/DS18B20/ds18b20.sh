#!/bin/bash
##File name: ds18b20.sh

TRUE=0
CHECK=`ls /sys/devices/ | grep "w1_bus*"`
NULL=

if [[ $CHECK = $NULL ]] ; then 
	echo "Device ds18b20 does not exit!"
	echo "Fail to get the temperature"
	exit
fi

echo "Please wait..."

#"w1_slave" is a file which records the temperature data 
ds18b20="w1_slave"

#Variable ds18b20_path is the path of "w1_slave"
ds18b20_path="/sys/devices/w1_bus_master1/"


#Different chip has different device_id, but there is a general number on the id_head -- "28"
chip_id=`ls $ds18b20_path | grep "28-"` 

ds18b20_path=${ds18b20_path}${chip_id}"/"${ds18b20}



#Cut the temperature string and convert it to real centigrade temperature
#The structure of w1_slave:
#################################################
#c0 01 4b 46 7f ff 0c 10 2e : crc=2e YES        #
#c0 01 4b 46 7f ff 0c 10 2e t=28000             #
#################################################

#Cut the temperature string
temper_str="t="
temper_str=`grep "t=" $ds18b20_path`
temper_str=${temper_str#*=}

#Convert the temperature string to real centigrade temperature
temper_high=${temper_str:0:2}
temper_low=${temper_str##$temper_high}
temper=${temper_high}"."${temper_low}




#Print the temperature into screen
if [[ $temper = "." ]] ; then
	echo "Fail to get temperature!"
else
	echo "The current temperature is "${temper}" Centigrade."
fi

#end
