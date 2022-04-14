// Sensor & motor director - Primary Arduino
#include "Adafruit_VL53L1X.h"	// ToF Sensor Control - VL53L1X
#include "MedianFilterLib2.h"	// Data noise filtering

#define timingBudget 20
#define motorSetPin 4

// ToF Sensor Declarations
#define IRQ_PIN 2
#define XSHUT_PIN 3
Adafruit_VL53L1X sensor = Adafruit_VL53L1X(XSHUT_PIN, IRQ_PIN);
MedianFilter2<int16_t> medianFilter2(7); // Median filter, 7 data point memory, returns the middle value out of them.

void tofSetup(int16_t tB);

void setup()
{
	// Setting up the Serial output.
    Serial.begin(115200);
    while(!Serial)  delay(10);
    Serial.println(F("Serial Link established."));

	// Setting up the sensor.
    tofSetup(timingBudget);
    Serial.println(F("Sensor configured."));

    // Setting up motor control.
    pinMode(motorSetPin, OUTPUT);
	digitalWrite(motorSetPin, LOW);
    Serial.println(F("Motor configured and set on."));	
}

void loop()
{
	int16_t sensorDistance;
	
	// if: new data is ready from the sensor, grab data.
	if (sensor.dataReady())
    {
		sensorDistance = sensor.distance();

		if(sensorDistance == -1) // Something went wrong!
		{
            Serial.print(F("Couldn't get distance: "));
            Serial.println(sensor.vl_status);
            return;
		}
		
		// Noise Filtering.
		int median = medianFilter2.AddValue(sensorDistance);
		
		Serial.print(sensorDistance);
		Serial.print(F(","));
		Serial.println(median);
		
		sensor.clearInterrupt();
	}
		
}

/*--------   ToF sensor setup   --------
**	timingBudget - the frequency that the sensor will read a data point.
**
**	There are unused control options here, currently unexplored.
*/
void tofSetup(int16_t tB)
{
	// Establishing Wire connection
    Wire.begin();
    if (! sensor.begin(0x29, &Wire)) // Signal start error check
    {
        Serial.print(F("Error on init of VL sensor: "));
        Serial.println(sensor.vl_status);
        while (1)       
        {
            Serial.print(F("."));
            delay(10);
        }
    }
    Serial.println(F("VL53L1X sensor OK!"));

    Serial.print(F("Sensor ID: 0x"));
    Serial.println(sensor.sensorID(), HEX);

	// Starting Ranging
    if (! sensor.startRanging()) // Ranging error check
    {
        Serial.print(F("Couldn't start ranging: "));
        Serial.println(sensor.vl_status);
        while (1)
        {
            Serial.print(F("."));
            delay(10);
        }
    }
    Serial.println(F("Ranging started"));

    // Valid timing budgets: 15, 20, 33, 50, 100, 200 and 500ms!
    sensor.setTimingBudget(tB);
    Serial.print(F("Timing budget (ms): "));
    Serial.println(sensor.getTimingBudget());

    /*
    vl.VL53L1X_SetDistanceThreshold(100, 300, 3, 1);
    vl.VL53L1X_SetInterruptPolarity(0);
    */
}