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

void test_advance_brightness_to_rollover() {
    sm.resetSettings();
    TEST_ASSERT_EQUAL(4, sm.getBrightness());
    sm.advanceBrightness();
    TEST_ASSERT_EQUAL(5, sm.getBrightness());
    sm.advanceBrightness();
    TEST_ASSERT_EQUAL(6, sm.getBrightness());
    sm.advanceBrightness();
    TEST_ASSERT_EQUAL(7, sm.getBrightness());
    sm.advanceBrightness();
    TEST_ASSERT_EQUAL(1, sm.getBrightness());
    sm.advanceBrightness();
    TEST_ASSERT_EQUAL(2, sm.getBrightness());
}

void test_advance_channel_to_rollover() {
    sm.resetSettings();
    TEST_ASSERT_EQUAL(8, sm.getChannel());
    sm.advanceChannel();
    TEST_ASSERT_EQUAL(1, sm.getChannel());
}

void test_advance_sensitivity_to_rollover() {
    sm.resetSettings();
    TEST_ASSERT_EQUAL(4, sm.getSensitivity());
    sm.advanceSensitivity();
    TEST_ASSERT_EQUAL(5, sm.getSensitivity());
    sm.advanceSensitivity();
    TEST_ASSERT_EQUAL(6, sm.getSensitivity());
    sm.advanceSensitivity();
    TEST_ASSERT_EQUAL(7, sm.getSensitivity());
    sm.advanceSensitivity();
    TEST_ASSERT_EQUAL(1, sm.getSensitivity());
}

void setup() {

  UNITY_BEGIN();
  delay(2000);

  RUN_TEST(test_settings_exist);
  RUN_TEST(test_set_settings);
  RUN_TEST(test_advance_brightness_to_rollover);
  RUN_TEST(test_advance_channel_to_rollover);
  RUN_TEST(test_advance_sensitivity_to_rollover);

  UNITY_END();
}

void loop() {}

#endif
