//smart_gloves.ino
#include <SoftwareSerial.h>
#include <avr/wdt.h>
#include "HitDetector.h"
int flag=0;
const int analogPin = A0;  // Analog input pin
const int resetButtonPin = 10;  // Reset button pin
const float knownResistor = 10000.0;  // Known resistor value
float defaultSensitivity = 39.0;  // Default hit sensitivity


int reset_btn=0;
String data;
HitDetector hitDetector(analogPin, knownResistor, defaultSensitivity,resetButtonPin );  // Create an instance of HitDetector

void setup() {
  
  Serial.begin(9600);  // Start serial communication with Arduino's built-in serial port
  pinMode(analogPin, INPUT);  // Set analog pin as input
  pinMode(resetButtonPin, INPUT);  // Set reset button pin as input
  
  while(!(digitalRead(resetButtonPin)));// stuck until the reset button pressed 
  flag=1;
  // Check if serial communication is established
  if (!Serial) {
    Serial.println("Serial communication not available. Check connections.");
    while (true);  // Loop indefinitely to halt the program
  }
}

void loop() {
  
  reset_btn = digitalRead(resetButtonPin);
  
  if ((reset_btn==1 && flag==0)||(data=='R')) {
  hitDetector.checkReset();  // the reset button is clicked
  //wdt_enable(WDTO_15MS); // Enable watchdog timer with a short timeout
  //while (true); // Wait for the watchdog timer to reset the Arduino
  flag=1;
  data='d';
  //delay(3000);
  }

  while(flag==1)
  {
  flag = hitDetector.getHitsPerMinute();
  //if(Serial.available()>0)
  //{
   
    //Serial.flush();
  //}
  }
  if (Serial.available() > 0) {  // Check if data is available from Bluetooth module
    float newSensitivity = Serial.read();  // Read the sensitivity value from Bluetooth
     //data=Serial.readString();
    hitDetector.updateSensitivity(newSensitivity);  // Update the hit sensitivity
  }
}
