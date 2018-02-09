#ifndef UNIT_TEST

#include <Arduino.h>
#include <StateManager.h>
#include <TapPressButton.h>
#include <Audio.h>

TapPressButton capSensor;
StateManager mainState;

const int capPin = 19;
const int touchTime = 1000;
unsigned long loopTime;
bool isTouch;

// Sound Library hooks & data
float soundLevel;                    // soundLevel could be an int
const int FFT_RESOLUTION = 1024;     // Do we need this at all?
float fftArray[FFT_RESOLUTION / 2];  // Do we need this at all?
float reading[8];                    // raw fft data of each 8 channels
int channelArray[8];                 // eq and scaled data of each 8 channels

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=139,91
AudioAnalyzeFFT1024      fft1024;        //xy=467,147
AudioAnalyzeRMS          rms1;           //xy=411,381
AudioConnection          patchCord1(i2s1, 0, fft1024, 0);
AudioConnection          patchCord2(i2s1, 0, rms1, 0);
// GUItool: end automatically generated code



//Global Varriables
int channel = 8;
int sensitivity = 4;  // 0-8 where 8 = maximum sensitivity

// This is low-level noise that's subtracted from each frequency band:
static const int noise[8] = {     // numbers generated using serial plotter at room tone at x10000 factor
  20, 05, 04, 06, 22, 64, 68, 89  // these are converted x 0.0001 later on before subtraction
};

static const int binStart[8] = { 
  0, 2, 3, 5, 9, 27, 99, 227       
};

static const int binEnd[8] = {  
  1, 2, 4, 8, 26, 98, 226, 511          
};

static const int scale[9] = {
  300, 1000, 3000, 6000, 10000, 20000, 30000, 50000, 100000   // sensitivity setting (mulitplication factor)
};

float eq[8] = {
  1.0, 1.0, 0.7, 0.5, 1.0, 1.0, 1.5, 2.0   // individual channel scaling factor
};


void analyzeFFT();
  // run FFT analysis function
  // store the resulting data to the `FFTArray` variable


void analyzeLevel();
  // run Level analysis function
  // store resulting value to the `soundLevel` variable


void setup() {
  Serial.begin(9600);
  AudioMemory(12);     // Audio requires memory to work.
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


void analyzeLevel() {
  if (rms1.available()) {
    soundLevel = (rms1.read() - 0.0006) * scale[sensitivity];     // remove noise and scale
    soundLevel = constrain(soundLevel, 0, 115);                   // limit
  }
}

void analyzeFFT() {
  if (fft1024.available()) {
    for (int i = 0; i < 8; i++) {
        reading[i] =  fft1024.read(binStart[i], binEnd[i]);
        reading[i] = reading[i] - (noise[i] * 0.0001);                // remove noise
        channelArray[i] = (reading[i] * scale[sensitivity]) * eq[i];  // scale
        channelArray[i] = constrain(channelArray[i], 0, 115);         // limit
    }
  }
}

#endif
