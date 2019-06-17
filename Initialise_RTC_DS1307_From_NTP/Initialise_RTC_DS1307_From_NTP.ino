/* Here I have initialised the RTC DS1307 RTC.begin(), time 
 *  with the time got from NTP.
 *  
 *  NTP's call in the setup(), getFormattedTime() which returns a string.
 *  This is passed into the RTCs initialisation RTC.begin()
 */

#include <Wire.h>
#include "RTClib.h"
#include <NTPClient.h>
// change next line to use with another board/shield
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid     = "NETGEAR84";
const char *password = "welcome2ibm";

RTC_Millis RTC;

String timestr;
String hourStamp, minStamp;
String minsec;

WiFiUDP ntpUDP;

// Note the 19800 = 5.5 hrs X 3600 in the third argument.
// Time zone set is IST.

NTPClient timeClient(ntpUDP,"europe.pool.ntp.org", 19800, 60000);

void setup () {
    Serial.begin(9600);

    //String buf;
    //buf = timeClient.getFormattedTime();

    /* NOTE: The RTC.begin () is typically initialized with the current
       date and time, with the __DATE__ and __TIME__ variables,

       But here I have collected the time from a NTP server in europe and 
       fed it to RTC.begin()
       The Date cannot be initialized from NTP as NTP only gets the current time !!!
       This is a drawback in the code.
     */

    // Previous Code.    
    //RTC.begin(DateTime(__DATE__, __TIME__ );    

    // Now, insert the time that you got from NTP above.
    RTC.begin(DateTime(__DATE__, timeClient.getFormattedTime().c_str()));    
}

void loop () {
    DateTime now = RTC.now();
    
    /*Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    */

    // Below, I retrieve time from both the NTP and RTC.
    // Both have to be accurate with no slip.

    
    Serial.print ("Current time after setting the NTP to RTC . ");
    
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.println(now.second(), DEC);
    
    Serial.print ( "Current time from NTP itself . " );
    Serial.println ( timeClient.getFormattedTime() );
    
    /*Serial.print( "*** *");
    Serial.print ( __TIME__ );
    Serial.println ("***");
    */
    delay(1000);
}
