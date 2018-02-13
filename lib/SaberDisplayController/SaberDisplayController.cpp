#include "SaberDisplayController.h"
#include <Adruino.h>
#include <FastLED.h>

SaberDisplayController::SaberDisplayController() {
  whiteFlag = false;
  prevTimerVal = 0;
}

void SaberDisplayController::setBrightness(int val) {
  DisplayController::setBrightness(val);
  FastLED.setBrightness(val);
}

void SaberDisplayController::setLevelPtr(float *lVal) { lVal = levelPtr; }
void SaberDisplayController::setFFTArray(float *fftArr) { fftArr = fftPtr; }

// get input values with these functions =============
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

int SaberDisplayController::getLevel() { return *levelPtr; }
int SaberDisplayController::getFFT() { return fftPtr; }
// ===== end input utility functions =================

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
