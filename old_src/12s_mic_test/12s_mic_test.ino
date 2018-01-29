#include <Audio.h>
//#include <Wire.h>
//#include <SPI.h>
//#include <SD.h>
//#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=325,243
AudioAnalyzeFFT256       fft;       //xy=503,250
AudioConnection          patchCord1(i2s1, 0, fft, 0);
// GUItool: end automatically generated code

int lastBin = 0;
int channelWidth = 1;

void setup() {
  Serial.begin(9600);
  AudioMemory(128);
}

void loop() {
  lastBin = 0;
  if (fft.available()) {
    for (int i=channelWidth; i<128; i+=channelWidth) {
      Serial.print(fft.read(lastBin, i) * 10);
      Serial.print(" | ");
      lastBin = i;
    }
    Serial.println();
  }
}
