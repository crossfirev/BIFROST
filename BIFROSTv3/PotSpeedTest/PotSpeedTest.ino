// Motor - Secondary Arduino
#include <AccelStepper.h>

#define motorPinPulMinus	7
#define motorPinDirMinus	6

AccelStepper motor(1, motorPinPulMinus, motorPinDirMinus);

void setup()
{
    Serial.begin(115200);
    while(!Serial) delay(10);
    Serial.println(F("Serial Running..."));
    motor.setMaxSpeed(20000);
    motor.setSpeed(100);
}

void loop()
{

}