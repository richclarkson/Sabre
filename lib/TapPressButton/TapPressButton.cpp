#include "TapPressButton.h"

TapPressButton::TapPressButton() {
  prevTimeStamp = 0;
  pressTime = 0;

  // set default values for button behavior
  debounceThreshold = 50;
  tapLength = 300;
  pressThreshold = 500;
  pressLength = 1000;
}

void TapPressButton::update(bool btnVal, unsigned long timerVal) {
  // This function should be called repeatedly in the main loop.
  if (btnVal) {
    updatePressTime(timerVal);
  } else {
    resetPressTime();
    resetTimeStamp();
  }
}

void TapPressButton::updatePressTime(unsigned long newTime) {
  if (newTime > prevTimeStamp) {
    pressTime += newTime - prevTimeStamp;
  }
}

bool TapPressButton::isTap() {
  return pressTime > debounceThreshold &&
         pressTime <= debounceThreshold + tapLength;
}

void TapPressButton::resetTimeStamp() { prevTimeStamp = 0; }

void TapPressButton::resetPressTime() { pressTime = 0; }
