#include <AFMotor.h>
#include <Servo.h>    

#define SERVO_PIN 9
          
Servo name_servo;               

int servo_position = 0 ;

void servoSetup() {
  
  // Define the servo signal pins
  name_servo.attach(SERVO_PIN);         

}

void servoLoop() {
 for (servo_position = 0; servo_position <=180; servo_position +=1){

    name_servo.write(servo_position);
    delay(10);
  }

  for (servo_position=180; servo_position >= 0; servo_position -=1){

    name_servo.write(servo_position);
    delay(10);
  }
}

