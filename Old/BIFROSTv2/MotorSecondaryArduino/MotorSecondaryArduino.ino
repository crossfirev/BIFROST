// Motor - Secondary Arduino
#include <AccelStepper.h>


#define motorAccepterPin	1

#define motorSpeed			10000
#define motorMaxSpeed	    10000
#define motorPinPulMinus	7
#define motorPinDirMinus	6

AccelStepper motor(1, motorPinPulMinus, motorPinDirMinus); // (1, 7, 6)

void setup()
{
	pinMode(motorAccepterPin, INPUT);
	motor.setMaxSpeed(motorMaxSpeed);
    motor.setSpeed(motorSpeed);
}

void loop()
{
	// Maybe I have to set motor.setSpeed() in setup
	if(digitalRead(motorAccepterPin) == LOW)
	{
        motor.runSpeed();
	}
}
