#include "SaberDisplayController.h"
#include <Arduino.h>
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

//TODO add a way for channel val to select a specific 'channel' from fftArr and rename it lVal
// ** There are getter methods for channel, brightness, and sensitivity, defined in the base class but avilable to this one. The values they return are updated whenever the values are changed by the StateManager, on a button press().
// getChannel()
// getSensitivity()
// getBrightness()

// ===== end input utility functions =================

void SaberDisplayController::turnOff() {
      for (int led = 0; led < NUM_LEDS; led++)        
  { //turn off LEDs
    leds[led] = CHSV( 100, 0, 0);
  }
}

void SaberDisplayController::displayFallingDot() {
  if (getLevel() > dot) dot = getLevel(); // Keep dot on top of lVal
  if (dot > NUM_LEDS) dot = NUM_LEDS; // Keep dot from going out of frame
  turnOff();
  for (int led = 0; led < getLevel(); led++)
  { // Start by Filling LEDS up to the lVal with dim white
    leds[led].setRGB(80, 80, 80);
  }
  leds[dot].setRGB(0, 0, 255);   // Fill in the 'peak' pixel with BLUE
  for (int led = dot + 1; led < NUM_LEDS; led++)
  { //make everything above the dot black
    leds[led].setRGB(0, 0, 0);
  }
  FastLED.show();
  if (++dotCount >= 60) {   // make the dot fall slowly
    dotCount = 0;
    if (dot > 1) {
      dot--;
    }
  }
}

void SaberDisplayController::displayMiddleOut() {
  turnOff();
  for (int led = (NUM_LEDS - getLevel()) / 2; led < (getLevel() / 2) + (NUM_LEDS / 2); led++)
  {
    leds[led].setRGB(50, 50, 50);
  }
  if (getLevel() <= 0)     // NO SOUND
  {                                    // If no sound (dot = 0)
    turnOff();
    leds[NUM_LEDS / 2].setRGB(80, 80, 80); // keep center dot illuminated
  }
  FastLED.show(); // send data to LEDs to display
}

void SaberDisplayController::displayRipple() {
  fadeToBlackBy( leds, NUM_LEDS, 1);   //turnOff();
  for (int y = 0; y < 8; y++) // create 8 different LED sections of saber each based on the 8 FFT channels
  {
    int bottomOfRipple = ((y * 15) + 6) - (getFFT()[y] / 10);
    if (bottomOfRipple <= 0)
    {
      bottomOfRipple = 0;
    }
    int topOfRipple = ((y * 15) + 6) + (getFFT()[y] / 10);
    if (topOfRipple >= NUM_LEDS - 1)
    {
      topOfRipple = NUM_LEDS - 1;
    }
    int rippleBrightness = constrain(getFFT()[y] * 3, 0, 254);
    for (int led = bottomOfRipple; led < topOfRipple; led++)
    {
      leds[led] = CHSV(0, 0, rippleBrightness); // fill in LEDs according to the top and bottom of each section deffined above
    }
    blur1d(leds, NUM_LEDS, getFFT()[y]);  // blur LEDs for smoother transitions
  }
  FastLED.show();
}

void SaberDisplayController::displayBangAndFade() {
    if (getLevel() > dot){ dot = getLevel(); } // Keep dot on top of lVal
  if (dot > NUM_LEDS){ dot = NUM_LEDS-1;  }  // Keep dot from going out of frame
  for (int led = 0; led < NUM_LEDS; led++)
  {
    leds[led] = CHSV( 100, 0, dot);
  }
  FastLED.show();
  if (++dotCount >= 10) {      // make the dot fall slowly
    dotCount = 0;
    if (dot > 5) {
      dot--;
    }
  }
}

void SaberDisplayController::displayRainbow() {
    fill_gradient(leds, 0, CHSV(96, 255,255) , NUM_LEDS, CHSV(0,255,255), SHORTEST_HUES);
    for (int led = getLevel(); led < NUM_LEDS; led++)        
  { //turn off LEDs
    leds[led] = CHSV( 100, 0, 0);
  }
  if (getLevel() <= 0)  { turnOff();  } // If no sound (dot = 0)
  FastLED.show(); 
}

// Lamp Mode Displays
void SaberDisplayController::displayNeon() {
  whiteFlag = false;
  rainbow(0, NUM_LEDS, 0.1);
}

void SaberDisplayController::displayWhite() {
  if (!whiteFlag) {
      for (int led = 0; led < NUM_LEDS; led++) {
        leds[led].setRGB( 150, 150, 150);
      }
      FastLED.show();
    whiteFlag = true;
  }
}

void SaberDisplayController::displayOmbre() {
  whiteFlag = false;
  rainbow(0, NUM_LEDS, 1);
}

void SaberDisplayController::displayFire() {
  whiteFlag = false;
  for (int led = 0; led < 100; led++) { 
    random16_add_entropy( random());
      Fire2012();
      FastLED.show(); // display this frame
      FastLED.delay(1000 / 60);
  }
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



void SaberDisplayController::rainbow(int startPos, int number, float deltaHue) {
  
    if (++rainbowCounter >= timeSpeed) {
      gHue++;
      rainbowCounter = 0;
    } // slowly cycle the "base color" through the rainbow
  
    fill_rainbow( &(leds[startPos]), number, gHue, deltaHue);
    FastLED.show();
  }

void SaberDisplayController::Fire2012()
  // Array of temperature readings at each simulation cell
  static byte heat[NUM_LEDS];

  // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUM_LEDS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUM_LEDS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < NUM_LEDS; j++) {
      CRGB color = HeatColor( heat[j]);
      int pixelnumber;
      if( gReverseDirection ) {
        pixelnumber = (NUM_LEDS-1) - j;
      } else {
        pixelnumber = j;
      }
      leds[pixelnumber] = color;
    }
}
