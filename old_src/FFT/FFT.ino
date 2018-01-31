
//Adapted from: Spectrum Analyzer Basic Example

/*
   Key varriables and Outputs:

     Sensitivity - from 0-8 to scale the sound readings accordingly

     Mode - ripple vs other music modes, if ripple then ignor specific channel setting and use FFT to output all 8 channel values

     Channel - all vs specific channel, if all then output RMS, if specific channel read and output only that channel

     Level - the cleaned and scaled sound reading output 0-115 to feed into the LED code. (For ripple this is 8 values)

*/

#include <Audio.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=139,91
AudioAnalyzeFFT1024      fft1024;        //xy=467,147
AudioAnalyzeRMS          rms1;           //xy=411,381
AudioConnection          patchCord1(i2s1, 0, fft1024, 0);
AudioConnection          patchCord2(i2s1, 0, rms1, 0);
// GUItool: end automatically generated code


// An array to hold the 8 frequency bands
float reading[8];    //TODO put bin numbers into an array here
int level[8];


// This is low-level noise that's subtracted from each frequency band:
static const int noise[8] = {   // numbers generated using serial plotter at room tone at x10000 factor
  20, 05, 04, 06, 22, 64, 68, 89            // these are converted x 0.0001 later on before subtraction
};

int sensitivity = 7;  // 0-8 where 8 = maximum sensitivity

static const int scale[9] = {
  300, 600, 1000, 2000, 5000, 10000, 15000, 50000, 100000   // sensitivity setting (mulitplication factor)
};

// Upper limit is used to clip readings off at a certian point set this as number of LEDs
const int upperLimit = 115;

// Lower threshold is used to make the readings more 'jumpy' at lower sensitvities.
static const int lowerThreshold[9] = {
  3, 2, 1, 0, 0, 0, 0, 0, 0
};





void setup() {
  AudioMemory(12);     // Audio requires memory to work.
  Serial.begin(9600);
}


void loop() {
  if (fft1024.available()) {

    // read the 512 FFT frequencies into 8 levels

    reading[0] =  fft1024.read(0, 1); //dark blue       // reading comes in at between 0.0 to 1.0
    reading[1] =  fft1024.read(2);  // red
    reading[2] =  fft1024.read(3, 4); // green
    reading[3] =  fft1024.read(5, 8); // orange
    reading[4] =  fft1024.read(9, 26); // purple
    reading[5] =  fft1024.read(27, 98);  // grey
    reading[6] =  fft1024.read(99, 226); // light blue
    reading[7] =  fft1024.read(227, 511);  //black


    for (int i = 0; i < 8; i++) {

      reading[i] = reading[i] - (noise[i] * 0.0001);           // remove noise
      level[i] = reading[i] * scale[sensitivity];                // scale

      if (level[i] > upperLimit) {
        level[i] = upperLimit;       // limiting
      }
      if (level[i] < lowerThreshold[sensitivity]) {
        level[i] = 0;                             // limiting
      }


      //Serial.print(level[i]);
      //Serial.print(" ");

    }




    if (rms1.available()) {

      int monoRms = (rms1.read() - 0.0006) * scale[sensitivity];     // remove noise and scale

      if (monoRms > upperLimit) {
        monoRms = upperLimit;      // limiting
      }
      if (monoRms < lowerThreshold[sensitivity]) {
        monoRms = 0;                            // limiting
      }

      Serial.print(monoRms);
      Serial.print("     ");
    }


    Serial.println(upperLimit);   // useful when stopping the serial plotter from autoscalling
  }
}



