import processing.serial.*;
import processing.sound.*;

Serial myPort;        // The  , ,l port
float inByte;         // Incoming ..serial data
boolean newData = false;
int xPos = 1;         // horizontal position of the graph
int scale = 200;

//Variables to draw a continuous line.
int lastxPos=1;
int lastheight=0;

//Sine Wave Oscillator
SinOsc sine;

void setup () {
  // set the window size:
  size(1200, 800);        

  myPort = new Serial(this, "/dev/cu.usbmodem14101", 9600);  

  // A serialEvent() is generated when a newline character is received :
  myPort.bufferUntil('\n');
  background(0);      // set inital background:
  
  background(0);
  colorMode(HSB, 360, 100, 100);
  noStroke();
  ellipseMode(RADIUS);
  frameRate(60);
  
  // create and start the sine oscillator.
  sine = new SinOsc(this);
  sine.play();
}
void draw () {
  if (newData) {
    drawGradient(width/2, height/2, inByte);
    
    //Sound
    //map knob from 0.0 to 1.0 for amplitude    
    //float amplitude = map(xPos, 0.0, width, 1.0, 0.0);
    //sine.amp(amplitude);
    
    //map knob from 20Hz to 1000Hz for frequency
    float frequency = map(inByte, 0, scale, 80.0, 1000.0);
    sine.freq(frequency);
    
   newData =false;
 }
}

void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');
  if (inString != null) {
    //print (inString);   
    inString = trim(inString);   // trim off whitespaces.
    inByte = float(inString);           // convert to a number.
    println (inByte);
    inByte = map(inByte, 0, scale, 0, height); //map to the screen height.
    newData = true; 
  }
}

void drawGradient(float x, float y, float d) {
  int radius = width/4;
  //float h = random(0, 360);
  float h = map(d, 0, height, 0, 360);
  for (int r = radius; r > 0; --r) {
    fill(h, 90, 90);
    ellipse(x, y, r, r);
    h = (h + 1) % 360;
  }
}
