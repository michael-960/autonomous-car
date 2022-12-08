#ifndef _CAR_H
#define _CAR_H

#include <AFMotor.h>

/*

   1  |--------------------|  2
      |                    |
      |                    |    --> front
      |                    |
   3  |--------------------|  4

*/

class Car {

  AF_DCMotor *motors;

public:
  AF_DCMotor *motor1, *motor2, *motor3, *motor4;

  uint8_t speed[4];
  uint8_t direction[4];

public:
  Car(AF_DCMotor *motors);

  void setMotorSpeed(int index, uint8_t direction, uint8_t speed);

  void forward(uint8_t speed);

  void backward(uint8_t speed);

  double avgSpeed();

  void left(uint8_t speed);

  void right(uint8_t speed);

  void release();
};

#endif
