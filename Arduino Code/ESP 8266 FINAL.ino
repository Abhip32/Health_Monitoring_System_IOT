#include "MAX30100_PulseOximeter.h"
#include <ezButton.h>
#include <ESP8266WiFi.h>
#include "ThingSpeak.h"
bool take=true;
#define REPORTING_PERIOD_MS     100

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


int i=1;
float avgBPM=0;
uint8_t avgSP=0;
String Temp="0";

#define REPORTING_PERIOD_MS     1000

// Create a PulseOximeter object
PulseOximeter pox;

// Time at which the last beat occurred
uint32_t tsLastReport = 0;

// Callback routine is executed when a pulse is detected
void onBeatDetected() {
    Serial.println("Beat!");
}

void setup() {
    Serial.begin(9600);

    Serial.print("Initializing pulse oximeter..");

    // Initialize sensor
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }

    // Register a callback routine
    pox.setOnBeatDetectedCallback(onBeatDetected);
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

    // Grab the updated heart rate and SpO2 levels
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        float BPM=pox.getHeartRate();
        Serial.print("Heart rate:");
        Serial.print(BPM);
        Serial.print("bpm / SpO2:");
        uint8_t SPO2=pox.getSpO2();
        Serial.print(SPO2);
        Serial.println("%");
       if(BPM!=0.0 && SPO2>=80)
       {
          Temp=Serial.readStringUntil('\n');
          Serial.println(Temp);
          ThingSpeak.writeField(myChannelNumber, FieldNumberBPM, BPM, myWriteAPIKey);
          ThingSpeak.writeField(myChannelNumber, FieldNumberOXI, SPO2, myWriteAPIKey);
          ThingSpeak.writeField(myChannelNumber, FieldNumberTemp,Temp , myWriteAPIKey);
       }
        tsLastReport = millis();
    }


    


}
