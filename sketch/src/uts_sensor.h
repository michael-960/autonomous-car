/*
 * Ultrasonic Sensor
 */

#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

class UltrasonicSensor {

private:
  uint8_t _echoPin, _trigPin;
  unsigned long _duration;

public:
  UltrasonicSensor(uint8_t echoPin, uint8_t trigPin) {

    this->_echoPin = echoPin;
    this->_trigPin = trigPin;
    pinMode(this->_echoPin, INPUT);  // Sets the echoPin as an INPUT
    pinMode(this->_trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  }

  double readDistance() {

    digitalWrite(this->_trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(this->_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->_trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    this->_duration = pulseIn(this->_echoPin, HIGH);
    // Calculating the distance
    return this->_duration * 0.034 / 2;
    // Speed of sound wave divided by 2 (go and back)
  }

}; // namespace sensor
#endif
