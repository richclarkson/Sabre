#ifndef AnalyzeSound_h  //guard - housekeeping, saying that if already included don't the rest of this code
#define AnalyzeSound_h

#include "Arduino.h"
#include "Audio.h"

class AnalyzeSound {    //encapsulated code
public:   // interface - useable in main
  void analyzeFFT();
  void analyzeFFTall();
  void analyzeLevel();
  float soundLevel;
  float fftArray[8];
  int fftSingle;
  int channel;
  int sensitivity;
  int upperLimit;
  

private:  // internal inner workings
  float reading[8];
  static const int noise[8];
  static const int binStart[8];
  static const int binEnd[8];
  static const int scale[9];
  float eq[8];
  void limit(int reading);
  void FFTreading(int FFTchannel);
};

#endif
