#include <NTPClient.h>
// change next line to use with another board/shield
#include <ESP8266WiFi.h>
//#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>

const char *ssid     = "Your_Wireless_Router_ID";
const char *password = "****Password****";

String timestr;
String hourStamp, minStamp;
String minsec;

WiFiUDP ntpUDP;

// Note the 19800 = 5.5 hrs X 3600 in the third argument.

NTPClient timeClient(ntpUDP,"europe.pool.ntp.org", 19800, 60000);

void setup(){
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
}

void loop() {
  timeClient.update();

  Serial.println(timeClient.getFormattedTime());

  delay(1000);

/*  Additional info for parsing Time and Minute.
  timestr =   timeClient.getFormattedTime();
  int splitT = timestr.indexOf(":");
  hourStamp = timestr.substring(0, splitT);
  Serial.print("Time ");
  Serial.print (atoi(hourStamp.c_str()));
  minsec= timestr.substring ( splitT+1, timestr.length());
  //Serial.print (" minsec = ");
  //Serial.print ( minsec );
  splitT = minsec.indexOf(":");
  minStamp = minsec.substring(0, splitT);
  Serial.print(" Min ");
  Serial.println (atoi(minStamp.c_str()));
  
  delay(1000);
*/

  /* additional info for parsing date and time if it is retrieved.
  Serial.println(timeClient.getFormattedDate());
  // Extract date
  int splitT = formattedDate.indexOf("T");
  dayStamp = formattedDate.substring(0, splitT);
  Serial.print("DATE: ");
  Serial.println(dayStamp);
  // Extract time
  timeStamp = formattedDate.substring(splitT+1, formattedDate.length()-1);
  Serial.print("HOUR: ");
  Serial.println(timeStamp);
  delay(1000);
  */
}
