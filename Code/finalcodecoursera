// THIS IS THE FINAL CODE PRODUCED DURING THE BIODATA PROCESSING GUIDED PROJECT AT COURSERA.
// USE IT IN ORDER TO HEAR THE SOUNDS PRODUCED WITH THE BIODATA VIA SINE OSCILLATOR. 
// COPY THE ENTIRE CODE, PASTE IT INTO THE PROCESSING IDE, AND MAKE SURE TO ADD THE DATASET YOU
// WANT TO LISTEN TO TO THE "DATA" FOLDER WITHIN YOUR PROCESSING SKETCH'S FOLDER.

import processing.sound.*;      //import the sound library

float inByte;      // Incoming data
int xPos = 1;      // horizontal position of the graph
int scale = 200;    // parameter to adjust audio-visual scale of map
int counter = 0;

//Variables to draw a continuous line.
int lastxPos=0;
int lastheight=0;

Table incoming_data; // table object to read the incoming data

SinOsc sine;      //Sine Oscilator

void setup (){
  size (600, 400);    // sets the window size
  incoming_data = loadTable("plant.csv", "header");    // loads the data into the table object
  println(incoming_data.getRowCount() + " total rows in table"); // print the total row # on table

  //create and start the sine oscillator
  sine = new SinOsc(this);
  sine.play();
 
  background(0);
  colorMode(HSB, 360, 100, 100);
  noStroke();
  ellipseMode(RADIUS);
  frameRate(60);
}

void draw(){
  inByte = incoming_data.getFloat(counter, "values");    // inBytes receives each data entry at a time
  float DrawData = map(inByte, 0, scale, 0, height);     // map data to fit screen
  println (counter + 1, inByte, DrawData);               // debugging
 
  drawGradient(width/2, height/2, DrawData);
  
  float frequency = map(DrawData, 0, height, 80.0, 1000.0);
  sine.freq(frequency);
  
  counter++;
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
