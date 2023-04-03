int lm35_pin = A0; //Connect the LM35 output to Analog Pin A0
float temp_celsius; // variable to store temperature in Celsius
#include <SoftwareSerial.h>
SoftwareSerial s(3,1);
void setup()
{
  s.begin(9600);
}

void loop()
{
  int sensor_value = analogRead(lm35_pin); // read the value from the LM35
  temp_celsius = (sensor_value * 500.0) / 1024.0;
  Serial.println("Temperature : "+String(temp_celsius));// Initialize serial communication at 9600 baud rate// convert the sensor value to Celsius
  s.write(temp_celsius);
  delay(1000);
}
