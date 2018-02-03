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
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <FastLED.h>      // v3.1.6
FASTLED_USING_NAMESPACE


// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=139,91
AudioAnalyzeRMS          rms1;           //xy=411,381
AudioConnection          patchCord1(i2s1, 0, rms1, 0);
// GUItool: end automatically generated code

int rmsReading = 2;       // store RMS reading
int prevrmsReading = 1;   // store the previous RMS reading


//LED Variables
#define DATA_PIN    7 // MOSI - Green on my strand
#define CLK_PIN     14 // SCK - Blue on my strand
#define LED_TYPE    APA102
#define COLOR_ORDER BRG
#define NUM_LEDS    115
CRGB leds[NUM_LEDS];

int dot;                 // A 'dot' to float on the top
int dotCount = 1;




void setup() {
  AudioMemory(12);     // Audio requires memory to work.
  Serial.begin(9600);

  // tell FastLED about the LED strip configuration
  //FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, DATA_PIN, CLK_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );

  FastLED.setBrightness(20);  // to save your eyeballs during testing
  FastLED.show();             // clear out any old data in the LEDs
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
  //delay(20);
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
    leds[led].setRGB( 0, 0, 0);
  }

  for (int led = 0; led < rmsReading; led++) {  // fill LEDs up to rmsReading with white
    leds[led].setRGB( 80, 80, 80);
  }

  if (rmsReading > dot) {
    dot = rmsReading;  // keep a 'dot' on top of rmsReading
  }

  leds[dot].setRGB( 0, 0, 255);             // set the dot as a blue pixel

  if (++dotCount >= 3) {                   // make the dot fall slowly
    dotCount = 0;
    if (dot > 1) {
      dot--;
    }
  }
  FastLED.show();
}



