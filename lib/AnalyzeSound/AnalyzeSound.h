#ifndef AnalyzeSound_h  //guard - housekeeping, saying that if already included don't the rest of this code
#define AnalyzeSound_h

class AnalyzeSound {    //encapsulated code
public:   // interface - useable in main
  void analyzeFFT();
  void analyzeFFTall();
  void analyzeLevel();
  int soundLevel;
  int fftArray[8];
  int fftSingle;
  int channel;
  int sensitivity;
  

private:  // internal inner workings
  AudioInputI2S            i2s1;           //xy=139,91
  AudioAnalyzeFFT1024      fft1024;        //xy=467,147
  AudioAnalyzeRMS          rms1;           //xy=411,381
  AudioConnection          patchCord1(i2s1, 0, fft1024, 0);
  AudioConnection          patchCord2(i2s1, 0, rms1, 0);

  float reading[8];
  static const int noise[8];
  static const int binStart[8];
  static const int binEnd[8];
  static const int scale[9];
  float eq[8];
  const int upperLimit;
  void limit(int reading);
  void FFTreading(int FFTchannel);
};

#endif
