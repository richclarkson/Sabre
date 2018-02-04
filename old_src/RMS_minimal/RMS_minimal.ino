/*
   Adapted from: Spectrum Analyzer Basic Example

   Set up:

    Ardunio 1.8.5 with Teensyduino 1.41

    Teensy 3.2  - 96 MHz (overclock)

    APA102 Leds (115 strand - powered by external 5v 4amp switching power supply)
      Data -> pin 7,
      Clock -> pin 14,
      GND -> GND

    ICS43434 I2S Digital Microphone
      CLK -> pin 9 (BCLK),
      WS -> pin 23 (LRCLK),
      Seial Data out -> pin 13.
      L/R -> GND
      3.3v -> 3.3v
      GND -> GND
*/


#include <Audio.h>     // v1.0.5
//#include <Wire.h>
//#include <SPI.h>
//#include <SD.h>
//#include <SerialFlash.h>
#include <FastLED.h>



// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=139,91
AudioAnalyzeRMS          rms1;           //xy=411,381
AudioConnection          patchCord1(i2s1, 0, rms1, 0);
// GUItool: end automatically generated code

int rmsReading = 2;       // store RMS reading
int prevrmsReading = 1;   // store the previous RMS reading

int NUM_LEDS = 115;
const uint16_t PixelCount = 115;

//LED Variables
// make sure to set this to the correct pins
const uint8_t DotClockPin = 14;
const uint8_t DotDataPin = 7;  

#define colorSaturation 128

// for software bit bang
NeoPixelBus<DotStarBgrFeature, DotStarMethod> strip(PixelCount, DotClockPin, DotDataPin);

RgbColor red(colorSaturation, 0, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor blue(0, 0, colorSaturation);
RgbColor white(colorSaturation);
RgbColor black(0);

int dot;                 // A 'dot' to float on the top
int dotCount = 1;




void setup() {
  AudioMemory(12);     // Audio requires memory to work.
  Serial.begin(9600);

      // this resets all the neopixels to an off state
    strip.Begin();
    strip.ClearTo(black);
    strip.Show();
}


void loop() {

  RMS();
  if (rmsReading != prevrmsReading) {
    Serial.print(rmsReading);
    Serial.print("     ");
    Serial.println(NUM_LEDS);    // useful when stopping the serial plotter from autoscalling
    prevrmsReading = rmsReading;
  }

  updateLEDs();
  //delay(10);
}



void RMS() {
  if (rms1.available()) {

    //rms1.read() gives a Float value between 0.0 and 1.0
    //Scale this by x2000 to roughly fit the 115 leds
    rmsReading = rms1.read() * 3000;     

    if (rmsReading > NUM_LEDS) {
      rmsReading = NUM_LEDS;              // upper limit
    }
    if (rmsReading < 0) {
      rmsReading = 0;                     // lower limit
    }
  }
}



void updateLEDs() {
  for (int led = 0; led < NUM_LEDS; led++) {  // set all LEDs to off
    strip.SetPixelColor(led, black);
  }

  for (int led = 0; led < rmsReading; led++) {  // fill LEDs up to rmsReading with white
    strip.SetPixelColor(led, white);
  }

  if (rmsReading > dot) {
    dot = rmsReading;  // keep a 'dot' on top of rmsReading
  }

  strip.SetPixelColor(dot, blue);             // set the dot as a blue pixel

  if (++dotCount >= 3) {                   // make the dot fall slowly
    dotCount = 0;
    if (dot > 1) {
      dot--;
    }
  }
  strip.Show();
}



