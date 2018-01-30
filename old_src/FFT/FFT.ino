
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
float level[8];
float prevLevel[8] = {0, 0, 0, 0, 0, 0, 0, 0};   // previous level reading used for falling dot and other music modes

int scale = 1024;

// This is low-level noise that's subtracted from each frequency band:
static const uint8_t noise[8] = {
  2, 1, 1, 1, 3, 6, 4, 4            // numbers generated using serial plotter at room tone
};

int sensitivity = 5;  // 0-8 where 8 = maximum sensitivity

// Upper limit is used to clip readings off at a certian point and set the scale to map to LEDs
static const int upperLimit[8] = {
  1024, 500, 250, 100, 50, 25, 10, 5     
};

// Lower threshold is used to make the readings more 'jumpy' at lower sensitvities.
static const int lowerThreshold[8] = {
  200, 20, 10, 0, 0, 0, 0, 0  
};





void setup() {
  AudioMemory(12);     // Audio requires memory to work.
  Serial.begin(9600);
}


void loop() {
  if (fft1024.available()) {

    // read the 512 FFT frequencies into 8 levels

    level[0] =  fft1024.read(0, 1); //dark blue
    level[1] =  fft1024.read(2);  // red
    level[2] =  fft1024.read(3, 4); // green
    level[3] =  fft1024.read(5, 8); // orange
    level[4] =  fft1024.read(9, 32); // purple
    level[5] =  fft1024.read(33, 131);  // grey
    level[6] =  fft1024.read(132, 257); // light blue
    level[7] =  fft1024.read(258, 511);  //black


    for (int i = 0; i < 8; i++) {

      level[i] = level[i] * scale;                // scalling
      level[i] = level[i] - noise[i];             // remove noise

      if (level[i] > upperLimit[sensitivity]) {
        level[i] = upperLimit[sensitivity];       // limiting
      }
      if (level[i] < lowerThreshold[sensitivity]) {
        level[i] = 0;                             // limiting
      }

      if (level[i] > prevLevel[i]) {
        prevLevel[i] = level[i];                  //falling
      }

      else {

        prevLevel[i] --;

      }

      if (prevLevel[i] < 0) {
        prevLevel[i] = 0;                        // limiting
      }


      //Serial.print(level[i]);
      //Serial.print(prevLevel[i]);   // print falling value
      //Serial.print(" ");

    }




    if (rms1.available()) {

      float monoRms = rms1.read() * scale;  //peak1.read outputs as a decimal from 1 (max) to 0 (min)

      //monoRms = monoRms - 2;                   // remove noise

      if (monoRms > upperLimit[sensitivity]) {
        monoRms = upperLimit[sensitivity];      // limiting
      }
      if (monoRms < lowerThreshold[sensitivity]) {
        monoRms = 0;                            // limiting
      }

      Serial.print(monoRms);
      Serial.print("     ");
    }





    Serial.println(upperLimit[sensitivity]);
    //Serial.println(200);
    //Serial.println("     ");
  }
}


