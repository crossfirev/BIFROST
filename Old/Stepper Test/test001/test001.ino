int driverPUL = 7;
int driverDIR = 6;

int pd = 1000;
bool setDir = LOW;

// Interupt Handler

void revMotor()
{
  setDir = !setDir;
}

void setup()
{
  pinMode(driverPUL, OUTPUT);
  pinMode(driverDIR, OUTPUT);
  
}

void loop() {
  if(pd <= 100)
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
  revMotor();
}
