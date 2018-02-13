#include "SaberDisplayController.h"
#include <Adruino.h>
#include <FastLED.h>

SaberDisplayController::SaberDisplayController() {
  whiteFlag = false;
  prevTimerVal = 0;
}

bool SaberDisplayController::isTimerUp(unsigned long timerVal,
                                       unsigned long timerLength) {
  if (timerVal = prevTimerVal > timerLength) {
    resetTimer(timerVal);
    return true;
  }
  return false;
}

void SaberDisplayController::resetTimer(unsigned long timerVal) {
  prevTimerVal = timerVal;
}

void SaberDisplayController::setBrightness(int val) {
  DisplayController::setBrightness(val);
  FastLED.setBrightness(val);
}

void SaberDisplayController::setLevelPtr(float *lVal) { lVal = levelPtr; }
void SaberDisplayController::setFFTArray(float *fftArr) { fftArr = fftPtr; }

int SaberDisplayController::getLevel() { return *levelPtr; }
int SaberDisplayController::getFFT() { return fftPtr; }

void SaberDisplayController::turnOff() {
  // include the code to turn off the LEDs here
}

void SaberDisplayController::displayFallingDot() {
  // add state display code here
}

void SaberDisplayController::displayMiddleOut() {
  // add state display code here
}

void SaberDisplayController::displayRipple() {
  // add state display code here
}

void SaberDisplayController::displayBangAndFade() {
  // add state display code here
}

void SaberDisplayController::displayRainbow() {
  // add state display code here
}

// Lamp Mode Displays
void SaberDisplayController::displayNeon() {
  whiteFlag = false;
  // add lamp display code here
}

void SaberDisplayController::displayWhite() {
  if (!whiteFlag) {
    // add lamp display code here
    whiteFlag = true;
  }
}

void SaberDisplayController::displayOmbre() {
  whiteFlag = false;
  // add lamp display code here
}

void SaberDisplayController::displayFire() {
  whiteFlag = false;
  // add lamp display code here
}

void SaberDisplayController::setChannel(int val) {
  DisplayController::setChannel(val);
  // add channel preview code here
}

void SaberDisplayController::setBrightness(int val) {
  DisplayController::setBrightness(val);
  // add channel preview code here
}

/*
Music Mode Preview Methods; These will likely change dramatically, but drop preview methods in here for now so I can figure out the best way to handle these.

It's a better idea to run these from the normal display chain, but I haven't quite figured out the best way yet. If I can't figure it out we can call these from the State constructors in the short term.

Make sure these run as blocking loops, using Arduino `delay()` to control timing. These won't be updateable mid-animation but they will display the preview.
*/

void SaberDisplayController::displayFallingDotPreview() {
  // place blocking display code here, using delays to get through the whole animation.
}

void SaberDisplayController::displayMiddleOutPreview() {
  // place blocking display code here, using delays to get through the whole animation.
}

void SaberDisplayController::displayRipplePreview() {
  // place blocking display code here, using delays to get through the whole
  // animation.
}

void SaberDisplayController::displayBangAndFadePreview() {
  // place blocking display code here, using delays to get through the whole
  // animation.
}

void SaberDisplayController::displayRainbowPreview() {
  // place blocking display code here, using delays to get through the whole
  // animation.
}
