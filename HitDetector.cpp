//HitDetector.cpp:
#include "HitDetector.h"

HitDetector::HitDetector(int analogPin, float knownResistor, float defaultSensitivity, int resetButtonPin)
  : analogPin(analogPin),
    knownResistor(knownResistor),
    previousResistance(0.0),
    previousTime(0),
    hitsPerMinute(0.0),
    sensitivity(defaultSensitivity),
    hitCount(0),
    startTime(0),
    resetTime(false),
    cycleCount(0),
    resetButtonPin(resetButtonPin) {
}



void HitDetector::checkReset() {
 // if (digitalRead(resetButtonPin)) {  // Check if reset button is pressed
    Serial.println("Timer has been reset");
    /*for (int i = 3; i > 0; i--) {  // Countdown before resetting
      Serial.println(i);
      delay(1000);
    }*/
    startTime = 0;  // Reset start time
    startTime = millis();
    cycleCount = 0;  // Reset cycle count
    hitCount=0;
  //}
}

int HitDetector::getHitsPerMinute() {
  previousResistance=5350.0;
  int reading = analogRead(analogPin);  // Read analog input
  float voltage = reading * (5.0 / 1023.0);  // Convert analog reading to voltage
  float resistance = (5.0 - voltage) / voltage * knownResistor;  // Calculate resistance
 
  int ret=1;
  unsigned long currentTime = millis();  // Get current time
  if (abs(resistance - previousResistance) >= sensitivity )//&& currentTime - previousTime <= 100) 
  {
    // Check if resistance has changed significantly within hit sensitivity threshold
    Serial.print("Hit;");
    hitCount++;  // Increment hit count
  } else {
    Serial.print("N/A;");
  }

  previousResistance = resistance;  // Update previous resistance
  previousTime = currentTime;  // Update previous time

  unsigned long elapsedTime = (currentTime + 1) - startTime;  // Calculate elapsed time
  int hitRate = hitCount / (elapsedTime / 60000.0);  // Calculate hit rate in hits per minute
  Serial.print(hitCount);
  //Serial.print(resistance);
  Serial.print(";");
  
  Serial.print(elapsedTime / 1000.0);
  Serial.print(" [seconds];");
  
  Serial.print(hitRate);
  Serial.print(";");

  Serial.println(sensitivity);


  //Serial.print(" hits/min; Elapsed time: ");
 delay(1009);
 if((elapsedTime/1000)==60 || (digitalRead(resetButtonPin)==HIGH ))
 {
   ret=0;
   return ret;
 }else 
 {
  //return hitRate;
  return ret;
 }
}
void HitDetector::updateSensitivity(float newSensitivity) {
  //Serial.print(newSensitivity);
  //Serial.print(";");

  sensitivity = newSensitivity;  // Update hit sensitivity
}
