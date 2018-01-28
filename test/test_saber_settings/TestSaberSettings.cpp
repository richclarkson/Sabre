#if defined(UNIT_TEST) && defined(ARDUINO)

#include "StateManager.h"
#include <Arduino.h>
#include <unity.h>

StateManager sm;

void setUp() { sm = StateManager(); }

void test_settings_exist() {
    Serial.begin(9600);
    sm.resetSettings();
    Serial.print("Channel: ");
    Serial.println(sm.getChannel());
    TEST_ASSERT_EQUAL(8, sm.getChannel());
    Serial.print("Sensitivity: ");
    Serial.println(sm.getSensitivity());
    TEST_ASSERT_EQUAL(4, sm.getSensitivity());
    Serial.print("Brightness: ");
    Serial.println(sm.getBrightness());
    TEST_ASSERT_EQUAL(4, sm.getBrightness());
}

void test_set_settings() {
  sm.resetSettings();
  TEST_ASSERT_EQUAL(4, sm.getSensitivity());
  TEST_ASSERT_EQUAL(4, sm.getBrightness());
  TEST_ASSERT_EQUAL(8, sm.getChannel());
}

void setup() {

  UNITY_BEGIN();
  delay(2000);

  RUN_TEST(test_settings_exist);
  RUN_TEST(test_set_settings);

  UNITY_END();
}

void loop() {}

#endif
