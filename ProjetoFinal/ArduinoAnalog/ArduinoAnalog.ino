#include <Wire.h>
#define NUM_SENSORS
int sensorPin[NUM_SENSORS] = {A0,A1};    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int sensorValue[2] = {0,0};  // variable to store the value coming from the sensor

void setup() {
  pinMode(ledPin, OUTPUT);// declare the ledPin as an OUTPUT:
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
}

void loop() {
  sensorValue[0] = analogRead(sensorPin[0]);// read the value from the sensor:
  sensorValue[1] = analogRead(sensorPin[1]);// read the value from the sensor:
  digitalWrite(ledPin, HIGH);// turn the ledPin on
  delay(sensorValue[0]);// stop the program for <sensorValue> milliseconds:
  digitalWrite(ledPin, LOW);// turn the ledPin off:
  delay(sensorValue[1]);  // stop the program for for <sensorValue> milliseconds:

}

void requestEvent() 
{
  
    unsigned char requested_Sensor_ID = Wire.read(); // Master sends SensorID as an int byte
    if(requested_Sensor_ID>NUM_SENSORS-1)
    {
      Serial.print("Some nasty stuff happened. Invalid ID!");
      Serial.println(requested_Sensor_ID)
       Wire.write('F');
      return
    }
    Wire.write(sensorValue[requested_Sensor_ID]); // receive byte as a character
    Serial.println(requested_Sensor_ID);         // print the character
  
}
