//HitDetector.h:
#ifndef HIT_DETECTOR_H
#define HIT_DETECTOR_H

#include <Arduino.h>

class HitDetector {
public:
  HitDetector(int analogPin, float knownResistor, float defaultSensitivity, int resetButtonPin);
  void checkReset();
  int getHitsPerMinute();
  void updateSensitivity(float newSensitivity);

private:
  int analogPin;  // Analog input pin
  float knownResistor;  // Known resistor value
  float previousResistance;  // Previous resistance value
  unsigned long previousTime;  // Previous time value
  float hitsPerMinute;  // Hits per minute
  float sensitivity;  // Hit sensitivity
  int hitCount;  // Number of hits
  unsigned long startTime;  // Start time
  bool resetTime;  // Flag to reset time
  int cycleCount;  // Cycle count
  int resetButtonPin;  // Reset button pin
  bool hitDetected  ;

};

#endif
