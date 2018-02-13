#ifdef UNIT_TEST

#include "StateManager.h"
#include "States.h"
#include <unity.h>

#include <iostream>
using namespace std;

class TestDisplayController : public DisplayController {
  int testValue;

public:
  TestDisplayController() { testValue = 0; }
  int getTestVal() { return testValue; }
  void turnOff() {
    testValue = 0;
  }
  void displayFallingDot() { testValue = 1; }
  void displayMiddleOut() {
    turnOff();
    testValue = 2;
  }
  void displayRipple() {
    turnOff();
    testValue = 3;
  }
  void displayBangAndFade() {
    turnOff();
    testValue = 4;
  }
  void displayRainbow() {
    turnOff();
    testValue = 5;
  }
  void displayNeon() { testValue = 10; }
  void displayWhite() { testValue = 20; }
  void displayOmbre() { testValue = 30; }
  void displayFire() { testValue = 40; }
};

StateManager sm;
TestDisplayController tdc;
unsigned long timerVal;

void setUp() {
  sm = StateManager(new NormalOff, new Neon);
  sm.registerDisplayController(&tdc);
}

void test_normal_off_system_state_calls_display_function() {
  sm.update();
  TEST_ASSERT_EQUAL(0, tdc.getTestVal());
}

void test_each_state_calls_its_display_function() {
  sm.update();
  TEST_ASSERT_EQUAL(0, tdc.getTestVal());
  sm.tap();
  sm.update();
  TEST_ASSERT_EQUAL(1, tdc.getTestVal());
  sm.tap();
  sm.update();
  TEST_ASSERT_EQUAL(2, tdc.getTestVal());
  sm.tap();
  sm.update();
  TEST_ASSERT_EQUAL(3, tdc.getTestVal());
  sm.tap();
  sm.update();
  TEST_ASSERT_EQUAL(4, tdc.getTestVal());
  sm.tap();
  sm.update();
  TEST_ASSERT_EQUAL(5, tdc.getTestVal());
  sm.tap();
  sm.tap();
  sm.update();
  TEST_ASSERT_EQUAL(0, tdc.getTestVal());
}

void test_display_controller_has_channel_setting() {
  TEST_ASSERT_EQUAL(8, tdc.getChannel());
}

void test_display_controller_has_sensitivity_setting() {
  TEST_ASSERT_EQUAL(4, tdc.getSensitivity());
}

void test_display_controller_has_brightness_setting() {
  TEST_ASSERT_EQUAL(4, tdc.getBrightness());
}

void test_display_channel_is_updated_by_state_manager() {
  TEST_ASSERT_EQUAL(8, tdc.getChannel());
  sm.press();
  sm.tap();
  sm.press();
  TEST_ASSERT_EQUAL(0, sm.getChannel());
  TEST_ASSERT_EQUAL(0, tdc.getChannel());
}

void test_display_sensitivity_is_updated_by_state_manager() {
  TEST_ASSERT_EQUAL(4, tdc.getSensitivity());
  sm.press();
  sm.tap();
  sm.tap();
  sm.press();
  TEST_ASSERT_EQUAL(5, tdc.getSensitivity());
}

void test_display_brghtness_is_updated_by_state_manger() {
  TEST_ASSERT_EQUAL(4, tdc.getBrightness());
  sm.press();
  sm.tap();
  sm.tap();
  sm.tap();
  sm.press();
  TEST_ASSERT_EQUAL(5, tdc.getBrightness());
}

int main() {
  UNITY_BEGIN();

  RUN_TEST(test_normal_off_system_state_calls_display_function);
  RUN_TEST(test_each_state_calls_its_display_function);
  RUN_TEST(test_display_controller_has_channel_setting);
  RUN_TEST(test_display_controller_has_sensitivity_setting);
  RUN_TEST(test_display_controller_has_brightness_setting);
  RUN_TEST(test_display_channel_is_updated_by_state_manager);
  RUN_TEST(test_display_sensitivity_is_updated_by_state_manager);
  RUN_TEST(test_display_brghtness_is_updated_by_state_manger);

  UNITY_END();
}

#endif
