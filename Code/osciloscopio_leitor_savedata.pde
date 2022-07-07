import processing.serial.*;

Serial myPort;        // The serial port
float inByte;         // Incoming serial data
boolean newData = false;
int xPos = 1;         // horizontal position of the graph 
int scale = 50;        // Adjust visual scale of map

Table registros;

//Variables to draw a continuous line.
int lastxPos=1;
int lastheight=0;

void setup () {
  // set the window size:
  size(800, 600);        

  myPort = new Serial(this, "/dev/cu.usbmodem1421", 9600);  

  // A serialEvent() is generated when a newline character is received :
  myPort.bufferUntil('\n');
  background(0);      // set inital background:
  
  registros = new Table();
  registros.addColumn("entry");
  registros.addColumn("values");
}
void draw () {
  if (newData) {
    // map data to fit screen
    float DrawData = map(inByte, 0, scale, 0, height);
    println (inByte, DrawData);
    
    //Drawing a line from Last inByte to the new one.
    float c = map(DrawData, 0, height, 0, 700);
    stroke(255, c, 0);     //stroke color
    strokeWeight(1);        //stroke wider 
    line(lastxPos, lastheight, xPos, height - DrawData); 
    
    lastxPos= xPos;
    lastheight= int(height - DrawData);

    // at the edge of the window, go back to the beginning:
    if (xPos >= width) {
      xPos = 0;
      lastxPos= 0;
      background(0);  //Clear the screen.
    } 
    else {
      // increment the horizontal position:
      xPos++;
    }
    
    //Table updating
    TableRow newRow = registros.addRow();
    newRow.setInt("entry", registros.lastRowIndex() + 1);
    newRow.setFloat("values", inByte);
    
    //Table saving
    saveTable(registros, "data/new.csv");
    
   newData =false;
 }
}

void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');
  if (inString != null) {
    //print (inString);
    inString = trim(inString);                // trim off whitespaces.
    inByte = float(inString);           // convert to a number.
    newData = true; 
  }
}
