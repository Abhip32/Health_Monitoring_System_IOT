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
String temp="";


void setup() {
    Serial.begin(9600);
      while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
      }
    // Initialize sensor
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }

    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
        }
  // Configure sensor to use 7.6mA for LED drive
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
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

   if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
      temp=Serial.read();
      ThingSpeak.writeField(myChannelNumber, FieldNumberTemp,temp, myWriteAPIKey);
      Serial.print("in DegreeC=   ");
      Serial.println(temp);

    String bp=String(pox.getHeartRate()/3);
    Serial.println("BPM"+bp);
    ThingSpeak.writeField(myChannelNumber, FieldNumberBPM, bp, myWriteAPIKey);
    String op=String(pox.getSpO2());
    Serial.println("OXI"+op);
    ThingSpeak.writeField(myChannelNumber, FieldNumberOXI, op, myWriteAPIKey);

    tsLastReport = millis();
  }
}