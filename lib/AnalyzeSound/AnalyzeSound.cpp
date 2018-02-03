#include "AnalyzeSound.h"
#include "Arduino.h"
#include "Audio.h"

AnalyzeSound::AnalyzeSound() {
  int soundLevel = 0;
  channel = 8;  // global channel setting
  sensitivity = 4;  // global sensitivity setting
  //fftArray[8];
  fftSingle = 0;
  reading[8]= { 0, 0, 0, 0, 0, 0, 0, 0 };
  noise[8] = { 20, 05, 04, 06, 22, 64, 68, 89 };
  binStart[8] = {0, 2, 3, 5, 9, 27, 99, 227 };
  binEnd[8] = {1, 2, 4, 8, 26, 98, 226, 511};
  scale[9] = {300, 1000, 3000, 6000, 10000, 20000, 30000, 50000, 100000};
  eq[8] = {1.0, 1.0, 0.7, 0.5, 1.0, 1.0, 1.5, 2.0};
  upperLimit = 115;
  
  AudioInputI2S            i2s1;           //xy=139,91
  AudioAnalyzeFFT1024      fft1024;        //xy=467,147
  AudioAnalyzeRMS          rms1;           //xy=411,381
  AudioConnection          patchCord1(i2s1, 0, fft1024, 0);
  AudioConnection          patchCord2(i2s1, 0, rms1, 0);

}

void AnalyzeSound::analyzeLevel() {
  if (rms1.available()) {
    soundLevel = (rms1.read() - 0.0006) * scale[sensitivity];     // remove noise and scale
    limit(soundLevel);
  }
}

void AnalyzeSound::analyzeFFT() {
  if (fft1024.available()) {
    FFTreading(channel)
    fftSingle = fftArray[FFTchannel];
  }
}

void AnalyzeSound::analyzeFFTall() {
if (fft1024.available()) {
    for (int i = 0; i < 8; i++) {
    FFTreading(i)
    }
  }
}

void AnalyzeSound::FFTreading(int FFTchannel){
      reading[FFTchannel] =  fft1024.read(binStart[FFTchannel], binEnd[FFTchannel]);
      reading[FFTchannel] = reading[FFTchannel] - (noise[FFTchannel] * 0.0001);           // remove noise
      fftArray[FFTchannel] = (reading[FFTchannel] * scale[sensitivity]) * eq[FFTchannel]; // scale
      limit(fftArray[FFTchannel]);
}

void AnalyzeSound::limit(int reading){
  if (reading > upperLimit) {
        reading = upperLimit;       // limit to number of LEDs
      }
      if (reading < 0) {
        reading = 0;               // limit to Zero
      }
}