
//Adapted from: Spectrum Analyzer Basic Example


#include <Audio.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=139,91
AudioAnalyzeFFT1024      fft1024;        //xy=467,147
AudioAnalyzeRMS          rms1;           //xy=411,381
AudioConnection          patchCord1(i2s1, 0, fft1024, 0);
AudioConnection          patchCord2(i2s1, 0, rms1, 0);
// GUItool: end automatically generated code


// An array to hold the 8 frequency bands
float level[8];    //TODO put bin numbers into an array here   


// This is low-level noise that's subtracted from each frequency band:
static const int noise[8] = {   // numbers generated using serial plotter at room tone 
  20, 05, 04, 06, 22, 64, 68, 89            // these are converted x 0.0001 later on before subtraction
};

int sensitivity = 4;  // 0-8 where 8 = maximum sensitivity


static const int scale[8] = {
  300, 600, 1000, 2000, 5000, 10000, 15000, 20000   // sensitivity setting 2
  };

// Upper limit is used to clip readings off at a certian point and set the scale to map to LEDs
const int upperLimit = 115;

// Lower threshold is used to make the readings more 'jumpy' at lower sensitvities.
static const int lowerThreshold[8] = {
  3, 2, 1, 0, 0, 0, 0, 0  
};





void setup() {
  AudioMemory(12);     // Audio requires memory to work.
  Serial.begin(9600);
}


void loop() {
  if (fft1024.available()) {

    // read the 512 FFT frequencies into 8 levels

    level[0] =  fft1024.read(0, 1); //dark blue       // reading comes in a two decimal value from 0.00 to 1.00
    level[1] =  fft1024.read(2);  // red
    level[2] =  fft1024.read(3, 4); // green
    level[3] =  fft1024.read(5, 8); // orange
    level[4] =  fft1024.read(9, 26); // purple
    level[5] =  fft1024.read(27, 98);  // grey
    level[6] =  fft1024.read(99, 226); // light blue
    level[7] =  fft1024.read(227, 511);  //black


    for (int i = 0; i < 8; i++) {
        
        level[i] = level[i] - (noise[i]*0.0001);             // remove noise
        level[i] = level[i] * scale[sensitivity];                // scalling
//
//      if (level[i] > upperLimit) {
//        level[i] = upperLimit;       // limiting
//      }
//      if (level[i] < lowerThreshold[sensitivity]) {
//        level[i] = 0;                             // limiting
//      }

     
      Serial.print(level[i]);
      Serial.print(" ");

    }




    if (rms1.available()) {

      int monoRms = rms1.read() * scale[sensitivity];  //peak1.read outputs as a decimal from 1 (max) to 0 (min)
      
      //monoRms = monoRms - 2;                   // remove noise

      if (monoRms > upperLimit) {
        monoRms = upperLimit;      // limiting
      }
      if (monoRms < lowerThreshold[sensitivity]) {
        monoRms = 0;                            // limiting
      }

      //Serial.print(monoRms);
      //Serial.print("     ");
    }



     //Serial.print(level[7]);
     //Serial.print("     ");
   
    Serial.println(upperLimit);
    //Serial.println(200);
    //Serial.println("     ");

  }
}

//void RMS(){
//    if (rms1.available()) {
//
//      float monoRms = rms1.read() * scale;  //peak1.read outputs as a decimal from 1 (max) to 0 (min)
//
//      //monoRms = monoRms - 2;                   // remove noise
//
//      if (monoRms > upperLimit[sensitivity]) {
//        monoRms = upperLimit[sensitivity];      // limiting
//      }
//      if (monoRms < lowerThreshold[sensitivity]) {
//        monoRms = 0;                            // limiting
//      }
//
//      Serial.print(monoRms);
//      Serial.print("     ");
//    }
//  }



