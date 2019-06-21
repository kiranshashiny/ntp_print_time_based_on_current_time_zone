#include <Arduino.h>
#include <TM1637Display.h>
#include <NTPClient.h>
// change next line to use with another board/shield
#include <ESP8266WiFi.h>
//#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>

// Module connection pins (Digital Pins)
#define CLK D3
#define DIO D4

#define CLK_2 D1
#define DIO_2 D2

const char *ssid     = "NETGEAR84";
const char *password = "welcome2ibm";

// The amount of time (in milliseconds) between tests
#define TEST_DELAY   500

const uint8_t SEG_DONE[] = {
	SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
	SEG_C | SEG_E | SEG_G,                           // n
	SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
	};

TM1637Display display(CLK, DIO);

TM1637Display display_2(CLK_2, DIO_2);

WiFiUDP ntpUDP;

// Note the 19800 = 5.5 hrs X 3600 in the third argument.
// This is for IST.
NTPClient timeClient(ntpUDP,"europe.pool.ntp.org", 19800, 60000);

String timestr;
String hourStamp, minStamp, hourminStamp;
String minsec;

void setup()
{

  Serial.begin(9600);

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
}

void loop()
{
  int k;
  uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
  uint8_t blank[] = { 0x00, 0x00, 0x00, 0x00 };
  display.setBrightness(0x00);
  display_2.setBrightness(0x00);
  delay(TEST_DELAY);

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
  display.setBrightness(0x0A);

  display.showNumberDec(atoi(hourminStamp.c_str()), true); // Expect: 0301
  delay ( TEST_DELAY);
  display.showNumberDecEx(atoi(hourminStamp.c_str()), (0x80 >> 1), true);
  delay(1000);
}
