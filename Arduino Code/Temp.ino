int lm35_pin = A0; //Connect the LM35 output to Analog Pin A0
float temp_celsius; // variable to store temperature in Celsius
#include <SoftwareSerial.h>
SoftwareSerial s(1,0);
void setup()
{
  Serial.begin(9600);
  s.begin(9600);
}

void loop()
{
  int sensor_value = analogRead(lm35_pin); // read the value from the LM35
  temp_celsius = (sensor_value * 500.0) / 1024.0;
  Serial.println(temp_celsius);
  delay(2000);
}
