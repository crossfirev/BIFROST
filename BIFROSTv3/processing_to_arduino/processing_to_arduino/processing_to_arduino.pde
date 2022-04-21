import processing.serial.*;

Serial myPort;        // The serial port
float inByte;         // Incoming serial data
boolean newData = false;
int xPos = 1;         // horizontal position of the graph 
float yPos = 0;

//Variables to draw a continuous line.
int lastxPos=1;
int lastheight=0;
int start = 0;

void setup()
{
  size(800, 600);
  String portName = Serial.list()[0]; //this should match 0, 1, 2 to match port
  myPort = new Serial(this, portName, 9600);
  background(#081640);
}

void draw () {
  beginShape();
  if (newData) {
    //Drawing a line from Last inByte to the new one.
    stroke(127,34,255);     //stroke color
    strokeWeight(1);        //stroke wider
    yPos = height - inByte;
    line(lastxPos, lastheight, xPos, yPos); 
    lastxPos= xPos;
    lastheight= int(height-inByte);
    
    
    //// at the edge of the window, go back to the beginning:
    //if (xPos >= width) {
    //  xPos = 0;
    //  lastxPos= 0;
    //  background(0);  //Clear the screen.
    //} 
    //else {
    //  // increment the horizontal position:
    //  xPos++;
    //}
   xPos++;
   newData =false;
 }
 endShape();
 //increment start
 start += 1;
}

void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');
  if (inString != null) {
    inString = trim(inString);                // trim off whitespaces.
    inByte = float(inString);           // convert to a number.
    inByte = map(inByte, 0, 1023, 0, height); //map to the screen height.
    newData = true; 
  }
}
