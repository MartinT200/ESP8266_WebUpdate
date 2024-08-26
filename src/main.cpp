
#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>

#include <time.h> 

#ifndef APSSID
#define APSSID "xxxxxxxx"
#define APPSK "xxxxxxxx"
#endif

ESP8266WiFiMulti WiFiMulti;
WiFiClient client;

time_t now;                         // this are the seconds since Epoch (1970) - UTC
tm tm;                              // the structure tm holds time information in a more convenient way

//https://werner.rothschopf.net/201802_arduino_esp8266_ntp.htm
/* Configuration of NTP */
#define MY_NTP_SERVER "at.pool.ntp.org"           
#define MY_TZ "CET-1CEST,M3.5.0/02,M10.5.0/03"  

#include "ota.h"  //OTA funktionen
#include "ntp.h"  //NTP funktionen

void setup() {
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(APSSID, APPSK);

  Serial.begin(115200);
  // Serial.setDebugOutput(false);
  delay(500);
  Serial.println();

  otaSetup();
  setupNTP();

  Serial.println("connecting to Wifi");
  while (WiFiMulti.run() != WL_CONNECTED) {
    delay(200);
    Serial.print ( "." );
  }
  Serial.println("\nWiFi connected");

  delay(2000);
  showTime();
  delay(2000);
}

int i = 10;                 // Starte OTA in 10 Sekunden!
long millisOld = millis();

void loop() {

  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    if (millis()-millisOld>1000){
      millisOld = millis();
      i--;
      Serial.println("Starte WebOTA in: " + String(i));
      if (i==0) {
        ota("http://raspberrypi.fritz.box/Blink.bin");
        i = 20; //falls Update fehlschlägt - neuer Versuch in 20s!
      }
    }
  }
}
