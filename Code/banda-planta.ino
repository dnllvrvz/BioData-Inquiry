int interruptPin = 1; // galvanometer input D1 no Ard. Uno
const byte samplesize = 4; // set sample array size
const byte analysize = samplesize - 1; // trim for analysis array
volatile unsigned long microseconds; // sampling timer
int ind = 0;
volatile word samples[samplesize];
float threshold = 0.1; // change threshold multiplier

int value = 0;
unsigned long antes = 0;
int intervalo = 10;

void sample()
{
  if(ind < samplesize) {
    samples[ind] = micros() - microseconds;
    microseconds = samples[ind] + microseconds;
    ind += 1;
    // Serial.println(samples[ind]);
  }
}

void analyzeSample()
{
  //eating up memory, one long at a time!
  word averg = 0;
  word maxim = 0;
  word minim = 65535;
  float stdevi = 0;
  word delta = 0;
  byte change = 0;

  if (ind == samplesize) { //array is full
    word sampanalysis[analysize];
    for (byte i=0; i<analysize; i++){ 
      //skip first element in the array
      sampanalysis[i] = samples[i+1];  //load analysis table (due to volitle)
      //manual calculation
      if(sampanalysis[i] > maxim) { maxim = sampanalysis[i]; }
      if(sampanalysis[i] < minim) { minim = sampanalysis[i]; }
      averg += sampanalysis[i];
      stdevi += sampanalysis[i] * sampanalysis[i];  //prep stdevi
    }
    //manual calculation
    averg = averg/analysize;
    stdevi = sqrt(stdevi / analysize - averg * averg); //calculate stdevu
    if (stdevi < 1) { stdevi = 1.0; } //min stdevi of 1
    delta = maxim - minim; 
    //**********perform change detection 
    if (delta > (stdevi * threshold)){
      change = 1;
    }
    //*********
    if(change){// set note and control vector
      value = averg;
    // Serial.println(value);
     }
     //reset array for next sample
      ind = 0;
  }
}

void setup() {
  Serial.begin(115200);
  attachInterrupt(interruptPin, sample, CHANGE);
  delay(500);
}

void loop() {
  unsigned long agora = millis();
  if ( ind >= samplesize ) { analyzeSample(); }
  if ( agora - antes >= intervalo )
    {
      antes = agora;
      Serial.println(value);
      
    }
}
