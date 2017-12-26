#include "SaberSettings.h"
#include <EEPROM.h>

void SaberSettingsClass::setSensitivity(char newVal) {
  EEPROM.put(sensitivityAddress, newVal);
}

char SaberSettingsClass::getSensitivity() {
  char val;
  EEPROM.get(sensitivityAddress, val);
  return val;
}

void SaberSettingsClass::setBrightness(char newVal) {
  EEPROM.put(brightnessAddress, newVal);
}

char SaberSettingsClass::getBrightness() {
  char val;
  EEPROM.get(brightnessAddress, val);
  return val;
}

void SaberSettingsClass::setChannels(char newVal) {
  EEPROM.put(channelsAddress, newVal);
}

char SaberSettingsClass::getChannels() {
  char val;
  EEPROM.get(channelsAddress, val);
  return val;
}

bool SaberSettingsClass::hasNoValues() {
  char sensitivityVal, brightnessVal, channelsVal;
  EEPROM.get(sensitivityAddress, sensitivityVal);
  EEPROM.get(brightnessAddress, brightnessVal);
  EEPROM.get(channelsAddress, channelsVal);
  return sensitivityVal == 0 && brightnessVal == 0 && channelsVal == 0;
}

void SaberSettingsClass::setDefaults() {
  EEPROM.put(sensitivityAddress, 4);
  EEPROM.put(brightnessAddress, 4);
  EEPROM.put(channelsAddress, 8);
}
