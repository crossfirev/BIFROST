#define aref_voltage 4.096

int ADCPin = 0; //using A1 input for this sketch
int ADCReading;

void setup()
{
Serial.begin(9600);

analogReference(EXTERNAL);
}

void loop(){

ADCReading = analogRead(A0);

Serial.print("ADC reading = ");
Serial.print(ADCReading); // the raw analog reading

// converting that reading to voltage, which is based off the reference voltage
float voltage = ADCReading * aref_voltage;
voltage /= 1024.0;

// print out the voltage
Serial.print(" – ");
Serial.print(voltage); Serial.println(" volts");

}