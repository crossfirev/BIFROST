/**
 * @author Matthew Lepis 
 * @email LepisMatthew@gmail.com
 * @create date 2022-04-06 20:31:01
 * @modify date 2022-04-12 21:23:04
 * @desc BIFROST Testbed Sensor Arduino codebase
 */

//------------------------------------------------------------------------------------------------------------
// User Variables       
//------------------------------------------------------------------------------------------------------------
//      'timingBudget'      - The frequency at which the VL53L1X (ToF sensor) retrieves data. UNITS: Hertz
//      'currAnalogPin'     - The analog pin that the signal output of the hall effect current sensor should be connected to.
#define timingBudget 20
#define currAnalogPin A0
//------------------------------------------------------------------------------------------------------------

#include "Adafruit_VL53L1X.h"	// ToF Sensor Control - VL53L1X
#include "MedianFilterLib2.h"	// Data noise filtering

// ToF Sensor Declarations, disregard unless you know what is happening here.
#define IRQ_PIN 2
#define XSHUT_PIN 3

// ToF & Distance data filter construction
Adafruit_VL53L1X sensor = Adafruit_VL53L1X(XSHUT_PIN, IRQ_PIN);
MedianFilter2<int16_t> medianFilterDis(7);      // Distance Median filter, 7 data point memory, returns the middle value out of them.    
void tofSetup(int16_t tB);

// Current Sensor data filter construction
MedianFilter2<float> medianFilterCurr(15);    // Current Median filter, 15 data point memory, returns the middle value out of them

void setup()
{
	// Setting up the Serial output.
    //      USB to PC
    Serial.begin(115200);
    while(!Serial)  delay(10);
    Serial.println(F("Serial Link established."));

	// Setting up the ToF sensor.
    //      Data obtained via I2C, connect SDA and SCL lines
    //      Power delivered to sensor via 3.3V or 5V, ensure GRD connected.
    tofSetup(timingBudget);
    Serial.println(F("ToF Sensor configured."));
    
    // No setup require for Current Sensor
    //      Data obtained via analog pin: 'currAnalogPin'
    //      Power delivered to sensor via 5V, ensure GRD connected.	

    // Motor is setup and ran via a secondary arduino. Not connected here.
}

void loop()
{
	int16_t sensorDistance;
    float currSenVoltage;
	
	// if: new data is ready from the sensor, grab data.
	if (sensor.dataReady())
    {
        // Storing current sensor values for cleaning.
		sensorDistance = sensor.distance();
        currSenVoltage = analogRead(currAnalogPin) * (5.0 / 1023.0);

		if(sensorDistance == -1) // Something went wrong!
		{
            Serial.print(F("Couldn't get distance: "));
            Serial.println(sensor.vl_status);
            return;
		}
		
		// Noise Filtering. Returns/stores cleaned data (Median of the last 'X' values, where 'X' is different for each of these two filters)
		int medianDis = medianFilterDis.AddValue(sensorDistance);
        float medianCurr = medianFilterCurr.AddValue(currSenVoltage);
		
        // Printing to Serial for PC capture
		Serial.print(medianDis);
		Serial.print(F(","));
		Serial.println(medianCurr);
		
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
	// Establishing I2C connection
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

    // Serial Sensor Identification
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