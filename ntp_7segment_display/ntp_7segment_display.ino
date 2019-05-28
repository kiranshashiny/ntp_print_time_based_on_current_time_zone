#include <NTPClient.h>
// change next line to use with another board/shield
#include <ESP8266WiFi.h>
//#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>
#include <TM1637Display.h>

const char *ssid     = "SSID";
const char *password = "Password";

// Module connection pins (Digital Pins)
#define CLK D6
#define DIO D7

// The amount of time (in milliseconds) between tests
#define TEST_DELAY   1000

TM1637Display display(CLK, DIO);

WiFiUDP ntpUDP;

// Note the 19800 = 5.5 hrs X 3600 in the third argument.
// This is for IST.
NTPClient timeClient(ntpUDP,"europe.pool.ntp.org", 19800, 60000);

String timestr;
String hourStamp, minStamp, hourminStamp;
String minsec;

void setup(){
  Serial.begin(9600);

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
  timestr =   timeClient.getFormattedTime();
  int splitT = timestr.indexOf(":");
  hourStamp = timestr.substring(0, splitT);
  //Serial.print("Time ");
  //Serial.print (atoi(hourStamp.c_str()));
  minsec= timestr.substring ( splitT+1, timestr.length());
  //Serial.print (" minsec = ");
  //Serial.print ( minsec );
  splitT = minsec.indexOf(":");
  minStamp = minsec.substring(0, splitT);
  //Serial.print(" Min ");
  //Serial.println (atoi(minStamp.c_str()));
  hourminStamp = hourStamp + minStamp; 
  Serial.println ( hourminStamp );
  display.setBrightness(0x0f);

  display.showNumberDec(atoi(hourminStamp.c_str()), true); // Expect: 0301
  delay ( TEST_DELAY);
  display.showNumberDecEx(atoi(hourminStamp.c_str()), (0x80 >> 1), true);

}
