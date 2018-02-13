#ifdef UNIT_TEST

#include "StateManager.h"
#include "States.h"
#include "TestStates.h"
#include <unity.h>

#include <iostream>
#include <typeinfo>
using namespace std;

StateManager sm;

void setUp(void) { sm = StateManager(new TestOne, new ColorOne); }

void setNonTestManager() { sm = StateManager(new NormalOff, new Neon); }

void test_state_value_exists() {
  TEST_ASSERT_EQUAL(1, sm.getCurrent()->getTestVal());
}

void test_state_advances_on_tap() {
  sm.tap();
  TEST_ASSERT_EQUAL(2, sm.getCurrent()->getTestVal());
  sm.tap();
  TEST_ASSERT_EQUAL(1, sm.getCurrent()->getTestVal());
  sm.tap();
  TEST_ASSERT_EQUAL(2, sm.getCurrent()->getTestVal());
}

void test_color_exists() { TEST_ASSERT_EQUAL(10, sm.getColor()->getTestVal()); }

void test_color_advances_when_two_is_pressed() {
  sm.tap(); // get to TestTwo
  sm.press();
  TEST_ASSERT_EQUAL(20, sm.getColor()->getTestVal());
  sm.press();
  TEST_ASSERT_EQUAL(10, sm.getColor()->getTestVal());
}

void test_channel_is_changed_when_pressed() {
  setNonTestManager();
  TEST_ASSERT_EQUAL(8, sm.getChannel());
  sm.press();
  sm.tap();
  sm.press();
  TEST_ASSERT_EQUAL(0, sm.getChannel());
}

void test_sensitivity_is_changed_when_pressed() {
  setNonTestManager();
  TEST_ASSERT_EQUAL(4, sm.getBrightness());
  sm.press();
  sm.tap();
  sm.tap();
  sm.press();
  TEST_ASSERT_EQUAL(5, sm.getSensitivity());
}

void test_brightness_is_changed_when_pressed() {
  setNonTestManager();
  TEST_ASSERT_EQUAL(4, sm.getBrightness());
  sm.press();
  sm.tap();
  sm.tap();
  sm.tap();
  sm.press();
  TEST_ASSERT_EQUAL(5, sm.getBrightness());
}

int main() {
  UNITY_BEGIN();

  RUN_TEST(test_state_value_exists);
  RUN_TEST(test_state_advances_on_tap);
  RUN_TEST(test_color_exists);
  RUN_TEST(test_color_advances_when_two_is_pressed);
  RUN_TEST(test_channel_is_changed_when_pressed);
  RUN_TEST(test_sensitivity_is_changed_when_pressed);
  RUN_TEST(test_brightness_is_changed_when_pressed);

  UNITY_END();
}

#endif
