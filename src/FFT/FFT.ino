//#include <LiquidCrystal.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=139,91
AudioAnalyzeFFT1024      fft1024;        //xy=467,147
AudioConnection          patchCord1(i2s1, 0, fft1024, 0);
// GUItool: end automatically generated code


// The scale sets how much sound is needed in each frequency range to
// show all 8 bars.  Higher numbers are more sensitive.
float scale = 1000.0;

// An array to hold the 16 frequency bands
float level[16];

// This array holds the on-screen levels.  When the signal drops quickly,
// these are used to lower the on-screen level 1 bar per update, which
// looks more pleasing to corresponds to human sound perception.
int   shown[16];



void setup() {
  // Audio requires memory to work.
  AudioMemory(12);

}


void loop() {
  if (fft1024.available()) {
    
    // read the 512 FFT frequencies into 16 levels
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

    level[0] =  fft1024.read(0, 1);
    level[1] =  fft1024.read(2, 6);
    level[2] =  fft1024.read(7, 15);
    level[3] =  fft1024.read(16, 32);
    level[4] =  fft1024.read(33, 66);
    level[5] = fft1024.read(67, 131);
    level[6] = fft1024.read(132, 257);
    level[7] = fft1024.read(258, 359);
    
    // See this conversation to change this to more or less than 16 log-scaled bands?
    // https://forum.pjrc.com/threads/32677-Is-there-a-logarithmic-function-for-FFT-bin-selection-for-any-given-of-bands

  
    for (int i=0; i<8; i++) {

      //Serial.print(level[i]);
      
      level[i] = level[i] * 10000;
      

      // TODO: conversion from FFT data to display bars should be
      // exponentially scaled.  But how keep it a simple example?
//      int val = level[i] * scale;
//      if (val > 8) val = 8;
//
//      if (val >= shown[i]) {
//        shown[i] = val;
//      } else {
//        if (shown[i] > 0) shown[i] = shown[i] - 1;
//        val = shown[i];
//      }

      Serial.print(level[i]);
      //Serial.print(shown[i]);
      Serial.print(" ");

    }
    Serial.println(0);
  } 
}


