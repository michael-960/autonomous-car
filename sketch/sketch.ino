#include <AFMotor.h>
#include <Adafruit_MotorShield.h>
#include <Servo.h>

#include <math.h>

#include "car.h"

#define FLAG

AF_DCMotor motors[] = {AF_DCMotor(1), AF_DCMotor(2), AF_DCMotor(3), AF_DCMotor(4)};

Car* car;

int counter = 0;

#ifdef FLAG

void setup() {

  sensorSetup();
  servoSetup();
  car = new Car(motors);
  counter = 0;
  
}


void loop() {
  
  double distance;

  distance = sensorReadDistance();

  car->left(200);
  delay(1000);

  car->release();
  delay(1000);

  
}

#else

void setup(){} 
void loop(){}

#endif

