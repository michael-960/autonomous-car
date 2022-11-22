#ifndef _CAR_H
#define _CAR_H


#include "AFMotor.h"

class Car {

  AF_DCMotor* motors;

  AF_DCMotor *motor1, *motor2, *motor3, *motor4;

  uint8_t speed[4];
  uint8_t direction[4];

  public:
    
    Car(AF_DCMotor* motors);

    void forward(uint8_t speed);

    void backward(uint8_t speed);

    void left(uint8_t speed, uint8_t angle);


    void release();

};

#endif
