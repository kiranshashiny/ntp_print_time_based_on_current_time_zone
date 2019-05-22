# ntp_print_time_based_on_current_time_zone

### This is code to get the current date and time from the NTP server converted to Indian Time Zone.


### This code is specific to ESP8266/NodeMcu, and to be uploaded thru Arduino IDE

The only key note in this sketch is that I have added the TZ conversion from the UTC to IST.

The IST is 5.5 hrs away from UTC.

The code uses 19800 in the third argument below, ( i.e 5.5 hrs multiplied by 3600 ( 3600 = 60 *60 seconds in a hour))
 

	NTPClient timeClient(ntpUDP,"europe.pool.ntp.org", 19800, 60000);

Set the right credentials to your wireless router in the code, Compile and Upload code to NodeMCU/ESP8266 thru the Arduino IDE, Open the Serial Monitor set at 115200 to see the current time in IST.

Good Luck.


Sample Output in the Serial Monitor is :
		
		
		12:14:44
		12:14:45
		12:14:46
		12:14:47
		12:14:48
		12:14:49
		12:14:50
