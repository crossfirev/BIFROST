// Library Inclusions.
#include "Adafruit_VL53L1X.h"
#include <AccelStepper.h>

// TOF Sensor Declarations.
#define IRQ_PIN 2
#define XSHUT_PIN 3
Adafruit_VL53L1X vl53 = Adafruit_VL53L1X(XSHUT_PIN, IRQ_PIN);

// Motor Declarations.
AccelStepper motor(1, 7, 6);

#define motorPin1 

void tofSetup();
void motorSetup();

void setup()
{
    // Setting up the Serial output.
    Serial.begin(115200);
    while(!Serial)  delay(10);
    Serial.println(F("Serial Link established."));

    // Setting up the sensor.
    TOFsetup();
    Serial.println(F("Sensor configured."));

    // Setting up motor contorl.
    motorSetup();
    Serial.println(F("Motor configured."));
}

void loop()
{
    int16_t distance;
/*
    if (vl53.dataReady())
    {
        // new measurement for the taking!
        distance = vl53.distance()/5;
        if (distance == -1)
        {
            // something went wrong!
            Serial.print(F("Couldn't get distance: "));
            Serial.println(vl53.vl_status);
            return;
        }
        /*Serial.print(F("Distance: "));
        Serial.print(distance);
        Serial.println(" mm");

        Serial.println(distance);
        motor.setSpeed(distance);

        // data is read out, time for another reading!
        vl53.clearInterrupt();
    }*/
    
    motor.runSpeed();

}

void TOFsetup()
{
    Wire.begin();
    if (! vl53.begin(0x29, &Wire))
    {
        Serial.print(F("Error on init of VL sensor: "));
        Serial.println(vl53.vl_status);
        while (1)       
        {
            Serial.print(F("."));
            delay(10);
        }
    }
    Serial.println(F("VL53L1X sensor OK!"));

    Serial.print(F("Sensor ID: 0x"));
    Serial.println(vl53.sensorID(), HEX);

    if (! vl53.startRanging())
    {
        Serial.print(F("Couldn't start ranging: "));
        Serial.println(vl53.vl_status);
        while (1)
        {
            Serial.print(F("."));
            delay(10);
        }
    }
    Serial.println(F("Ranging started"));

    // Valid timing budgets: 15, 20, 33, 50, 100, 200 and 500ms!
    vl53.setTimingBudget(20);
    Serial.print(F("Timing budget (ms): "));
    Serial.println(vl53.getTimingBudget());

    /*
    vl.VL53L1X_SetDistanceThreshold(100, 300, 3, 1);
    vl.VL53L1X_SetInterruptPolarity(0);
    */
}

//
void motorSetup()
{
    motor.setMaxSpeed(200);
    motor.setSpeed(100);
}