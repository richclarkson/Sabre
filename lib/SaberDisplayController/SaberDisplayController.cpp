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
      for (int led = 0; led < NUM_LEDS; led++)        
  { //turn off LEDs
    leds[led] = CHSV( 100, 0, 0);
  }
}

void SaberDisplayController::displayFallingDot() {
  if (soundLevel > dot) dot = soundLevel; // Keep dot on top of soundLevel
  if (dot > NUM_LEDS) dot = NUM_LEDS; // Keep dot from going out of frame
  turnoffLEDs();
  for (int led = 0; led < soundLevel; led++)
  { // Start by Filling LEDS up to the soundLevel with dim white
    leds[led].setRGB(80, 80, 80);
  }
  leds[dot].setRGB(0, 0, 255);   // Fill in the 'peak' pixel with BLUE
  for (int led = dot + 1; led < NUM_LEDS; led++)
  { //make everything above the dot black
    leds[led].setRGB(0, 0, 0);
  }
  FastLED.show(); // send data to LEDs to display
  if (++dotCount >= 60) {   // make the dot fall slowly
    dotCount = 0;
    if (dot > 1) {
      dot--;
    }
  }
}

void SaberDisplayController::displayMiddleOut() {
  turnoffLEDs();
  for (int led = (NUM_LEDS - soundLevel) / 2; led < (soundLevel / 2) + (NUM_LEDS / 2); led++)
  {
    leds[led].setRGB(50, 50, 50);
  }
  if (soundLevel <= 0)     // NO SOUND
  {                                    // If no sound (dot = 0)
    turnoffLEDs();
    leds[NUM_LEDS / 2].setRGB(80, 80, 80); // keep center dot illuminated
  }
  FastLED.show(); // send data to LEDs to display
}

void SaberDisplayController::displayRipple() {
  fadeToBlackBy( leds, NUM_LEDS, 1);
  //turnoffLEDs();

  for (int y = 0; y < 8; y++) // create 8 different LED sections of saber each based on the 8 FFT channels
  {
    int bottomOfRipple = ((y * 15) + 6) - (fftArray[y] / 10);
    if (bottomOfRipple <= 0)
    {
      bottomOfRipple = 0;
    }
    int topOfRipple = ((y * 15) + 6) + (fftArray[y] / 10);
    if (topOfRipple >= NUM_LEDS - 1)
    {
      topOfRipple = NUM_LEDS - 1;
    }
    int rippleBrightness = constrain(fftArray[y] * 3, 0, 254);
    for (int led = bottomOfRipple; led < topOfRipple; led++)
    {
      leds[led] = CHSV(0, 0, rippleBrightness); // fill in LEDs according to the top and bottom of each section deffined above
    }
    blur1d(leds, NUM_LEDS, fftArray[y]);  // blur LEDs for smoother transitions
  }

  FastLED.show();
}

void SaberDisplayController::displayBangAndFade() {
    if (soundLevel > dot){ dot = soundLevel; } // Keep dot on top of soundLevel
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
    for (int led = soundLevel; led < NUM_LEDS; led++)        
  { //turn off LEDs
    leds[led] = CHSV( 100, 0, 0);
  }
  if (soundLevel <= 0)  { turnoffLEDs();  } // If no sound (dot = 0)
  FastLED.show(); 
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
