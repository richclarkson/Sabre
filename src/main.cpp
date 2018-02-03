#ifndef UNIT_TEST

#include <Arduino.h>
#include <StateManager.h>
#include <TapPressButton.h>
#include <AnalyzeSound.h>
#include <Audio.h>

TapPressButton capSensor;
StateManager mainState;

const int capPin = 19;
const int touchTime = 1000;
unsigned long loopTime;
bool isTouch;

// Sound Library hooks & data
float soundLevel;
//float fftArray [8];
int fftSingle;

const int FFT_RESOLUTION = 256;
float fftArray[FFT_RESOLUTION / 2];

void analyzeFFTall() {
  // run FFT analysis function 
  // used by Ripple Mode
  // store the resulting data to the `FFTArray` variable
}

void analyzeFFT() {
  // run FFT analysis function 
  // used by the Music Modes (excluding Ripple Mode) when specific channel IS set 
  // store resulting value to the `fftSingle` variable
}

void analyzeLevel() {
  // run (RMS) Level analysis function 
  // used by the Music Modes (excluding Ripple Mode) when specific channel IS NOT set 
  // store resulting value to the `soundLevel` variable
}

void setup() {
  Serial.begin(9600);
  loopTime = 0;
  capSensor = TapPressButton(50, 300, 1000, 1000);
  mainState = StateManager();
  mainState.registerFFT(analyzeFFT, &fftArray[0]);
  mainState.registerLevel(analyzeLevel, &soundLevel);
  isTouch = false;
}

void loop() {
  isTouch = touchRead(capPin) > touchTime;
  loopTime = millis();
  // Serial.println(touchRead(capPin));
  capSensor.update(isTouch, loopTime);
  if (capSensor.isTap()) {
    mainState.tap();
  }
  if (capSensor.isPress()) {
    mainState.press();
  }
  mainState.update();
}

#endif
