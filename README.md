# ntp_print_time_based_on_current_time_zone

# This is code to get the current date and time from the NTP server converted to Indian Time Zone.

The only key note in this blog is that I have added the TZ conversion from the UTC to IST.

The IST is 5.5 hrs away from UTC.


The code uses 19800 ( i.e 5.5 hrs multiplied by 3600 ( 3600 = 60 *60 seconds in a hour))
 

	NTPClient timeClient(ntpUDP,"europe.pool.ntp.org", 19800, 60000);

Set the right credentials to your wireless router in the code, Compile and Upload code to ESP8266 thru the Arduino IDE, Open the Serial Monitor set at 115200 to see the current time in IST.

Good Luck.
