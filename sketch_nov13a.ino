
#include <AFMotor.h>
#include <Adafruit_MotorShield.h>

#include "car.h"

#define FLAG 1


AF_DCMotor motors[] = {AF_DCMotor(1), AF_DCMotor(2), AF_DCMotor(3), AF_DCMotor(4)};

Car* car;

int counter = 0;

void setup() {

  car = new Car(motors);

  if (FLAG) {
    sensorSetup();
  }

}



void loop() {
  
  double distance;

  if (FLAG) {
    distance = sensorReadDistance();
    
    Serial.println(distance);

    if (counter % 400 == 0) {
      car->release();
      delay(100);
      car->forward(200);
    }

    if (counter % 400 == 200) {
      car->release();
      delay(100);
      car->backward(200);
    }

    delay(10);

    counter += 1;
    counter %= 400;
  }
}

