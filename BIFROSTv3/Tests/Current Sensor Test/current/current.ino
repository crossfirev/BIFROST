#include "MedianFilterLib2.h"
MedianFilter2<float> medianFilter2(200);


void setup()
{
    Serial.begin(115200);
    while(!Serial)  delay(10);
    Serial.println(F("Serial Link established."));

    pinMode(1, OUTPUT);
    digitalWrite(1, HIGH);
}

void loop()
{
    float voltageIn = analogRead(A0) * (5.0/1023.0);
    float median = medianFilter2.AddValue(voltageIn);

    //Serial.print(voltageIn);
    //Serial.print(F(","));
    Serial.println(median);
}
