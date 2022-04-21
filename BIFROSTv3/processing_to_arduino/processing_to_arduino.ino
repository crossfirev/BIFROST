void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop()
{
  //send 'Hello, world!' over the serial port
  //Serial.println("Hello, world!");
  long randNumber = random(300);
  Serial.println(randNumber);
  //wait 100 milliseconds so we don't drive ourselves crazy
  delay(100);
}
