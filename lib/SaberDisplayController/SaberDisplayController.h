#ifndef SaberDisplayController_h
#define SaberDisplayController_h

#include "StateManager.h"

class SaberDisplayController : public DisplayController {
  bool whiteFlag;
  unsigned long prevTimerVal;
  float* levelPtr;
  float* fftPtr;

public:
  SaberDisplayController();

  void turnOff();
  void update(StateManager *sm);

  bool isTimerUp(unsigned long timerVal, unsigned long timerLength);
  void resetTimer(unsigned long timerVal);
  
  void displayFallingDot();
  void displayMiddleOut();
  void displayRipple();
  void displayBangAndFade();
  void displayRainbow();
  
  void displayNeon();
  void displayWhite();
  void displayOmbre();
  void displayFire();

  void displayFallingDotPreview();
  void displayMiddleOutPreview();
  void displayRipplePreview();
  void displayBangAndFadePreview();
  void displayRainbowPreview();

  void setLevelPtr(float *lVal);
  void setFFTArray(float *fftArr);

  void setChannel(int val);
  void setSensitivity(int val);
  void setBrightness(int val);

  int getLevel();
  int getFFT() { return fftPtr; }
};

#endif
