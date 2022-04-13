#include "Adafruit_VL53L1X.h"

#define IRQ_PIN 2
#define XSHUT_PIN 3
Adafruit_VL53L1X vl53 = Adafruit_VL53L1X(XSHUT_PIN, IRQ_PIN);

int driverPUL = 7;
int driverDIR = 6;

int pd = 1000;
bool setDir = LOW;

void sensorTOFLoop()
{
    int16_t sensedDistance;

    if(vl53.dataReady())
    {
        // A new measurement is ready!
        sensedDistance = vl53.distance();
        if(sensedDistance == -1)
        {
            // Error, something went wrong.
            Serial.print(F("Couldn't get distance: "));
            Serial.println(vl53.vl_status);
            return;
        }
        //Serial.print(F("Distance: "));
        Serial.println(sensedDistance);
        //Serial.println(" mm");

		// Data is printed, indicate for another reading.
		vl53.clearInterrupt();
    }
}

void sensorTOFSetup()
{
    Wire.begin();
    if(! vl53.begin(0x29, &Wire)) // Initializes the vl53l1x sensor, if failed: Error output and hang.
    {
        Serial.print(F("Error on init of VL sensor: "));
        Serial.println(vl53.vl_status);
        while (1) delay(10);
    }
    Serial.println(F("VL53L1X sensor OK!"));

    Serial.print(F("Sensor ID: 0x"));
    Serial.println(vl53.sensorID(), HEX);

    if(! vl53.startRanging()) // Begin sensor's ranging
    {
        Serial.print(F("Couldn't start ranging: "));
        Serial.println(vl53.vl_status);
        while (1)   delay(10);
    }
    Serial.println(F("Ranging started"));

    // Valid timing budgets: 15, 20, 33, 50, 100, 200 and 500ms!
    vl53.setTimingBudget(50);
    Serial.print(F("Timing budget (ms): ")) ;
    Serial.println(vl53.getTimingBudget());

    /*
    vl.VL53L1X_SetDistanceThreshold(100, 300, 3, 1);
    vl.VL53L1X_SetInterruptPolarity(0);
    */
}

// Interupt Handler

void revMotor()
{
  setDir = !setDir;
}

void setup()
{
  pinMode(driverPUL, OUTPUT);
  pinMode(driverDIR, OUTPUT);
  
  Serial.begin(115200);
  while(!Serial) delay(10);
  sensorTOFSetup();
}

void loop() {
  /*if(pd <= 100)
  {
    pd = 1000;
  }
  pd = pd - 100;
  for(int i = 0; i < 1000; i++)
  {
    digitalWrite(driverDIR, setDir);
    digitalWrite(driverPUL, HIGH);
    delayMicroseconds(pd);
    digitalWrite(driverPUL, LOW);
    delayMicroseconds(pd);
  }
  revMotor();*/
  sensorTOFLoop();
}


