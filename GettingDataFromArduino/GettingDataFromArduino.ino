#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#define REPORTING_PERIOD_MS 1000

// Create a PulseOximeter object
PulseOximeter pox;
int outputpin= A0;
// Time at which the last beat occurred
uint32_t tsLastReport = 0;

//----------- Enter you Wi-Fi Details---------//
char ssid[] = "Redmi";     //SSID
char pass[] = "12345677";  // Password
//-------------------------------------------//

WiFiClient client;

unsigned long myChannelNumber = 2052369;  // Channel ID here
const int FieldNumberTemp = 1;
const int FieldNumberBPM = 2;
const int FieldNumberOXI = 3;
const char* myWriteAPIKey = "GSNDTRVHC7K6GXV1";  // Your Write API Key here

void setup() {
  Serial.begin(9600);
   if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  // Configure sensor to use 7.6mA for LED drive
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
}
void loop() {

  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, pass);
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }



  pox.update();

  // Grab the updated heart rate and SpO2 levels
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
  int analogValue = analogRead(outputpin);
  float millivolts = (analogValue/1024.0) * 3000; //3300 is the voltage provided by NodeMCU
  float celsius = millivolts/10;
  String tem=String(celsius);
  ThingSpeak.writeField(myChannelNumber, FieldNumberTemp,tem, myWriteAPIKey);
  Serial.print("in DegreeC=   ");
  Serial.println(celsius);

    String bp=String(pox.getHeartRate());
    Serial.println("BPM"+bp);
    ThingSpeak.writeField(myChannelNumber, FieldNumberBPM, bp, myWriteAPIKey);
    String op=String(pox.getSpO2());
    Serial.println("OXI"+op);
    ThingSpeak.writeField(myChannelNumber, FieldNumberOXI, op, myWriteAPIKey);

    tsLastReport = millis();
  }

}