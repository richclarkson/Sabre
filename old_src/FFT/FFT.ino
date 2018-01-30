
//Adapted from: Spectrum Analyzer Basic Example


#include <Audio.h>
//#include <Wire.h>
//#include <SPI.h>
//#include <SD.h>
//#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=139,91
AudioAnalyzeFFT1024      fft1024;        //xy=467,147
AudioAnalyzePeak         peak1;          //xy=317,123
AudioAnalyzeRMS          rms1;           //xy=411,381
AudioConnection          patchCord1(i2s1, 0, fft1024, 0);
AudioConnection          patchCord2(i2s1, peak1);
AudioConnection          patchCord3(i2s1, 0, rms1, 0);
// GUItool: end automatically generated code


 // An array to hold the 8 frequency bands
 float level[8];
 float prevLevel[8];

 int scale = 1024;
 //int upperLimit = 100;  // set the peak limit, lower = more sensitive but more clipping
 int lowerLimit = 10;     // set the lower threshold, lower = more sensitive but more noise


  // This is low-level noise that's subtracted from each frequency band:
 static const uint8_t noise[8] = {
    2, 1, 1, 1, 3, 6, 4, 4     //  5, 6, 10, 18, 30, 35, 55, 20
  };


 int sensitivity = 4;

    // This is sensitivity settings
 static const int upperLimit[8] = {
    5, 10, 25, 50, 100, 250, 500, 1024     //  5, 6, 10, 18, 30, 35, 55, 20
  };

 static const int lowerThreshold[8] = {
    0, 2, 5, 7, 10, 20, 50, 200     //  5, 6, 10, 18, 30, 35, 55, 20
  }; 
  





void setup() {
  // Audio requires memory to work.
  AudioMemory(12);
  Serial.begin(9600);

  for (int i=0; i<8; i++) {   prevLevel[i] = 0;  }  // clear out prevLevel values
    


}


void loop() {
  if (fft1024.available()) {
    
    // read the 512 FFT frequencies into 8 levels
    // music is heard in octaves, but the FFT data
    // is linear, so for the higher octaves, read
    // many FFT bins together.
    
    // these are the example 16 levels 
    
//    level[0] =  fft1024.read(0);
//    level[1] =  fft1024.read(1);
//    level[2] =  fft1024.read(2, 3);
//    level[3] =  fft1024.read(4, 6);
//    level[4] =  fft1024.read(7, 10);
//    level[5] =  fft1024.read(11, 15);
//    level[6] =  fft1024.read(16, 22);
//    level[7] =  fft1024.read(23, 32);
//    level[8] =  fft1024.read(33, 46);
//    level[9] =  fft1024.read(47, 66);
//    level[10] = fft1024.read(67, 93);
//    level[11] = fft1024.read(94, 131);
//    level[12] = fft1024.read(132, 184);
//    level[13] = fft1024.read(185, 257);
//    level[14] = fft1024.read(258, 359);
//    level[15] = fft1024.read(360, 511);

    // merged 16 levels into 8     

    //TODO re-written more cleanly

    level[0] =  fft1024.read(0,1);  //dark blue
    level[1] =  fft1024.read(2);  // red
    level[2] =  fft1024.read(3,4);  // green
    level[3] =  fft1024.read(5,8);  // orange
    level[4] =  fft1024.read(9,32);  // purple
    level[5] =  fft1024.read(33, 131);  // grey
    level[6] =  fft1024.read(132, 257); // light blue
    level[7] =  fft1024.read(258, 511);  //black





    
    // See this conversation to change this to more or less than 16 log-scaled bands?
    // https://forum.pjrc.com/threads/32677-Is-there-a-logarithmic-function-for-FFT-bin-selection-for-any-given-of-bands

  
    for (int i=0; i<8; i++) {

      //Serial.print(level[i]);
      
      level[i] = level[i] * scale;  // scalling
      level[i] = level[i] - noise[i];     // remove noise

      if (level[i] > upperLimit[sensitivity]){ level[i] = upperLimit[sensitivity];  }   // limiting
      if (level[i] < lowerThreshold[sensitivity]){ level[i] = 0; }      // limiting

      if (level[i] > prevLevel[i]){  prevLevel[i] = level[i];   }   //falling

      else { 
        
        prevLevel[i] --; 
        
        }

       if (prevLevel[i] < 0){ prevLevel[i] = 0; }      // limiting


      //Serial.print(level[i]);
      //Serial.print(prevLevel[i]);

      //Serial.print(" ");

    }

    
    if (peak1.available()) {
     
      float monoPeak = peak1.read() * scale;  //peak1.read outputs as a decimal from 1 (max) to 0 (min)

      monoPeak = monoPeak - 2;  // remove noise
      
      if (monoPeak > upperLimit[sensitivity]){ monoPeak = upperLimit[sensitivity];  }   // limiting
      if (monoPeak < lowerThreshold[sensitivity]){ monoPeak = 0; }      // limiting
      
      Serial.print(monoPeak);
      Serial.print("     ");
    }




    if (rms1.available()) {
     
      float monoRms = rms1.read() * scale;  //peak1.read outputs as a decimal from 1 (max) to 0 (min)

      monoRms = monoRms - 2;  // remove noise
      
      if (monoRms > upperLimit[sensitivity]){ monoRms = upperLimit[sensitivity];  }   // limiting
      if (monoRms < lowerThreshold[sensitivity]){ monoRms = 0; }      // limiting
      
      Serial.print(monoRms);
      Serial.print("     ");
    }




    
    Serial.println(upperLimit[sensitivity]);
    //Serial.println(200);
    //Serial.println("     ");
  } 
}


