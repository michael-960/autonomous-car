#include "car.h"

Car::Car(AF_DCMotor *motors) {

  this->motors = motors;

  this->motor1 = motors;
  this->motor2 = motors + 1;
  this->motor3 = motors + 2;
  this->motor4 = motors + 3;

  for (int i = 0; i < 4; ++i) {
    this->speed[i] = 0;
    this->direction[i] = RELEASE;
  }
}

void Car::forward(uint8_t speed) {
  for (int i = 0; i < 4; ++i) {
    this->setMotorSpeed(i, FORWARD, speed);
  }
}

void Car::backward(uint8_t speed) {
  for (int i = 0; i < 4; ++i) {
    this->setMotorSpeed(i, BACKWARD, speed);
  }
}

void Car::left(uint8_t speed) {

  for (int i = 0; i < 4; ++i) {
    if (i >= 2) {
      this->setMotorSpeed(i, FORWARD, speed);
    } else {
      this->setMotorSpeed(i, BACKWARD, speed);
    }
  }
}

void Car::right(uint8_t speed) {

  for (int i = 0; i < 4; ++i) {
    if (i < 2) {
      this->setMotorSpeed(i, FORWARD, speed);
    } else {
      this->setMotorSpeed(i, BACKWARD, speed);
    }
  }
}

void Car::release() {
  for (int i = 0; i < 4; ++i) {
    this->setMotorSpeed(i, RELEASE, 0);
  }
}

double Car::avgSpeed() {

  double tot = 0.;
  for (int i = 0; i < 4; ++i) {
    if (this->direction[i] == FORWARD)
      tot += this->speed[i];

    if (this->direction[i] == BACKWARD)
      tot -= this->speed[i];
  }
  return tot / 4.;
}

void Car::setMotorSpeed(int index, uint8_t direction, uint8_t speed) {

  (this->motors + index)->run(direction);
  (this->motors + index)->setSpeed(speed);

  this->speed[index] = speed;
  this->direction[index] = direction;
}
