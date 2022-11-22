

const uint8_t SPEED = 8;

const int TIME = 2000;

void motorSetup4() {
  
  for(int i=0; i<4; ++i) {
    motors[i].setSpeed(SPEED);
	  motors[i].run(RELEASE); 
  }
  
}

void motorLoop4() { 

  uint8_t speed = 150;

  for(int i=0; i<4; ++i) {
    motors[i].run(FORWARD);
    motors[i].setSpeed(speed);
  }

  delay(1000);

  for(int i=0; i<4; ++i) {
    motors[i].run(BACKWARD);
    motors[i].setSpeed(speed);
  }
  
  delay(1000);

  for(int i=0; i<4; ++i) {
    motors[i].run(RELEASE);
  }
  delay(20);
  

}

void moveMotors(AF_DCMotor* motors, int n) {
  uint8_t i;

	// Turn on motor
  for (int m=0; m<n; m++)
	  motors[m].run(FORWARD);
	
	// Accelerate from zero to maximum speed
	for (i=0; i<255; i++) 
	{
    for (int m=0; m<n; m++)
		  motors[m].setSpeed(i); 

		delay(10);
	}
	
	// Decelerate from maximum speed to zero
	for (i=255; i!=0; i--) 
	{
    for (int m=0; m<n; m++)
	  	motors[m].setSpeed(i);  
      
		delay(10);
	}

	// Now change motor direction
  for (int m=0; m<n; m++)
  	motors[m].run(BACKWARD);
	
	// Accelerate from zero to maximum speed
	for (i=0; i<255; i++) 
	{
    for (int m=0; m<n; m++)
	  	motors[m].setSpeed(i);  
		delay(10);
	}

	// Decelerate from maximum speed to zero
	for (i=255; i!=0; i--) 
	{
    for (int m=0; m<n; m++)
		  motors[m].setSpeed(i);  
		delay(10);
	}

	// Now turn off motor
  for (int m=0; m<n; m++) {
	  motors[m].run(RELEASE);
  }
	delay(1000);
}