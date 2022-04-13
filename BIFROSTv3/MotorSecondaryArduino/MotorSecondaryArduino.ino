/**
 * @author Matthew Lepis 
 * @email LepisMatthew@gmail.com
 * @create date 2022-04-06 20:31:01
 * @modify date 2022-04-12 21:25:19
 * @desc BIFROST Testbed Motor Arduino codebase
 */

// AccelStepper Lib, used for motor control.
#include <AccelStepper.h>

// Motor Speed Settings
//      Stepper Motor RPM = ('motorSpeed' / 'Microstep Setting) * 60s
//          'microStepSetting'  - The microstep setting on the digital stepper driver. UNITS: Pulses per revolution
//          'motorSpeed'        - This isn't user defined in the code, but address via the potentiometer. Found otherwise via 'motor.speed()'. UNITS: Steps per second AKA Pulses per second.
//          'motorMaxSpeed'     - Clamped maximum speed of the motor. UNITS: Steps per second AKA Pulses per second. 
#define microStepSetting    10000
#define motorMaxSpeed	    200000

// Motor Pin Definitions
//      'motorPinPulMinus'      - Digital pin for motor pulse minus.        The positive pin is just 5V.
//      'motorPinDirMinus'      - Digital pin for motor direction minus.    The positive pin is just 5V.
#define motorPinPulMinus	7
#define motorPinDirMinus	6

// Motor Function Toggle Definitions
//      'motorRunTogglePin'     - Digital pin for toggling the stepping of the motor. !CAUTION - This does not turn off the motor, just pauses stepping! Unless changed, this is the red toggle.
//      'motorDirTogglePin'     - Digital pin for toggling the direction stepped by the motor. Unless changed, this is the black toggle.
#define motorRunTogglePin	53
#define motorDirTogglePin   52

// AccelStepper motor construction
AccelStepper motor(1, motorPinPulMinus, motorPinDirMinus); // (1, 7, 6)

void setup()
{   
    // Stepper Direction Toggle
    //      In pinin pullup configuration. Short this pin to ground to bring this low.
    pinMode(motorDirTogglePin, INPUT_PULLUP);

    // Stepper Run Toggle
    //      In pinin pullup configuration. Short this pin to ground to bring this low.
	pinMode(motorRunTogglePin, INPUT_PULLUP);

    // Stepper Start Parameters
	motor.setMaxSpeed(motorMaxSpeed);
    motor.setSpeed(100);
    //motor.setAcceleration(1);         // This specific (accel set to 1) function is called via setSpeed() I think.
}

void loop()
{
    // If 'motorRunTogglePin' is low, STOP STEPPING.
	if(digitalRead(motorRunTogglePin) == LOW)
	{
        motor.runSpeed();        
        short potSignal = analogRead(A0);

        // If 'motorDirTogglePin' is low, rotate motor forward, else reverse.
        if(digitalRead(motorDirTogglePin) == LOW)
        {
            // Switch speed based on potentiometer signal, maps voltage range (0-1023) to 5 different speed levels
            switch(potSignal)
            {
                case 0 ... 204:
                    motor.setSpeed(.1*microStepSetting);    // 10% 
                case 205 ... 408:
                    motor.setSpeed(.25*microStepSetting);   // 25%
                case 409 ... 612:
                    motor.setSpeed(.5*microStepSetting);    // 50%
                case 613 ... 816:
                    motor.setSpeed(microStepSetting);       // 100%
                case 817 ... 1023:
                    motor.setSpeed(2*microStepSetting);     // 200%
            }
        }
        else
        {
            // Switch speed based on potentiometer signal, maps voltage range (0-1023) to 5 different speed levels
            switch(potSignal)
            {
                case 0 ... 204:
                    motor.setSpeed(-.1*microStepSetting);    // 10% 
                case 205 ... 408:
                    motor.setSpeed(-.25*microStepSetting);   // 25%
                case 409 ... 612:
                    motor.setSpeed(-.5*microStepSetting);    // 50%
                case 613 ... 816:
                    motor.setSpeed(-microStepSetting);       // 100%
                case 817 ... 1023:
                    motor.setSpeed(-2*microStepSetting);     // 200%
            }
        }

	}
    /* DEBUG, Runs the motor for 'timer' milliseconds. Must declare 'long timer' in 'setup()' function. Detects 'failed' steps.
    long time = millis();
    if(time < timer)
    {
        if(motor.runSpeed())
        {
            //Serial.print(F("SUC, "));
            //Serial.println(millis());
        }
        else
        {
            //Serial.print(F("ERR, "));
            //Serial.println(millis());
        }
    }
    else
    {
        Serial.println(F("Done."));
    }*/
}