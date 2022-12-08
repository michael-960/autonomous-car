#include "sketch.h"
#include "car.h"
#include "serial_comm.h"
#include "uts_sensor.h"
#include <AFMotor.h>
#include <Servo.h>

#define SERVOPIN 9

namespace __sketch_private {
Car *car;
UltrasonicSensor *sensor;
Servo servo;

SerialProcessor *serialProcessor;
uint8_t *parseResult;
} // namespace __sketch_private

using namespace __sketch_private;

void sketch::setup() {

  Serial.begin(9600);
  serialProcessor = new SerialProcessor(4);
  parseResult = new uint8_t[4];

  AF_DCMotor motors[] = {AF_DCMotor(1), AF_DCMotor(2), AF_DCMotor(3),
                         AF_DCMotor(4)};
  car = new Car(motors);
  sensor = new UltrasonicSensor(33, 32);
  servo.attach(SERVOPIN);

  servo.write(180);
  delay(500);
  servo.write(0);
  delay(500);
  servo.write(90);
  Serial.println("__arduino_started__");
}

void sketch::loop() {

  double distance;
  distance = sensor->readDistance();
  Serial.println(distance);

  while (Serial.available()) {
    serialProcessor->push(Serial.read());
  }
  serialProcessor->parseLast(parseResult);

  switch (parseResult[0]) {

  case 0:
    break;
  case 1:
    car->forward(parseResult[1]);
    break;
  case 2:
    car->backward(parseResult[1]);
    break;
  case 3:
    car->left(parseResult[1]);
    break;
  case 4:
    car->right(parseResult[1]);
    break;
  case 5:
    car->release();
    break;
  case 6:
    servo.write(parseResult[1]);
    break;
  default:;
  }
}
