
#include "car.h"

Car::Car(AF_DCMotor* motors) {
  this->motors = motors;

  this->motor1 = motors;
  this->motor2 = motors+1;
  this->motor3 = motors+1;
  this->motor4 = motors+1;

  for (int i=0; i<4; ++i) {
    this->speed[i] = 0;
    this->direction[i] = RELEASE;
  }

}

void Car::forward(uint8_t speed) {
  for(int i=0; i<4; ++i) {
    (this->motors + i)->run(FORWARD);
    (this->motors + i)->setSpeed(speed);
    this->speed[i] = speed;
    this->direction[i] = FORWARD;
  }
}

void Car::backward(uint8_t speed) {
  for(int i=0; i<4; ++i) {
    (this->motors + i)->run(BACKWARD);
    (this->motors + i)->setSpeed(speed);
    this->speed[i] = speed;
    this->direction[i] = BACKWARD;
  }
}

void Car::left(uint8_t speed, uint8_t angle) {

  //this->motor1->;
}

void Car::release() {
  for(int i=0; i<4; ++i) {
    (this->motors + i)->run(RELEASE);
    this->direction[i] = RELEASE;
  }
    
}