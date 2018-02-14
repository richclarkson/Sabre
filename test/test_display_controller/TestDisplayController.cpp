#ifdef UNIT_TEST

#include "StateManager.h"
#include "States.h"
#include <unity.h>

#include <iostream>
using namespace std;

class TestDisplayController : public DisplayController {
  int testValue;
  int testBrightnessVal;
  unsigned long prevTimerVal;

public:
  TestDisplayController() { 
    testValue = 0; 
    testBrightnessVal = 0;
    prevTimerVal = 0;
  }
  void setBrightness(int val) {
    // cout << "\nBB: " << val << "\n";
    DisplayController::setBrightness(val);
    testBrightnessVal = val;
  }
  int getTestVal() { return testValue; }
  int getTestBrightnessVal() { return testBrightnessVal; }
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
  
  bool hasTimerPassed(unsigned long timerVal, unsigned long timerLength) {
    if (timerVal - prevTimerVal > timerLength) {
      resetTimer(timerVal);
      return true;
    }
    return false;
  }
  void resetTimer(unsigned long timerVal) {
    prevTimerVal = timerVal;
  }
  int getTestPtr(int *val) {
    return *val;
  }
};

StateManager sm;
TestDisplayController tdc;
unsigned long timerVal;

void setUp() {
  sm = StateManager(new NormalOff, new Neon);
  sm.registerDisplayController(&tdc);
}

void test_normal_off_system_state_calls_display_function() {
  sm.updateDisplay();
  TEST_ASSERT_EQUAL(0, tdc.getTestVal());
}

void test_each_state_calls_its_display_function() {
  sm.updateDisplay();
  TEST_ASSERT_EQUAL(0, tdc.getTestVal());
  sm.tap();
  sm.updateDisplay();
  TEST_ASSERT_EQUAL(1, tdc.getTestVal());
  sm.tap();
  sm.updateDisplay();
  TEST_ASSERT_EQUAL(2, tdc.getTestVal());
  sm.tap();
  sm.updateDisplay();
  TEST_ASSERT_EQUAL(3, tdc.getTestVal());
  sm.tap();
  sm.updateDisplay();
  TEST_ASSERT_EQUAL(4, tdc.getTestVal());
  sm.tap();
  sm.updateDisplay();
  TEST_ASSERT_EQUAL(5, tdc.getTestVal());
  sm.tap();
  sm.tap();
  sm.updateDisplay();
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

void test_child_brightness_setting_is_changed() {
  TEST_ASSERT_EQUAL(4, tdc.getTestBrightnessVal());
  sm.press();
  sm.tap();
  sm.tap();
  sm.tap();
  sm.press();
  TEST_ASSERT_EQUAL(5, tdc.getBrightness());
  TEST_ASSERT_EQUAL(5, tdc.getTestBrightnessVal());
}

void test_timer_val() {
  TEST_ASSERT_FALSE(tdc.hasTimerPassed(100, 300));
  tdc.resetTimer(1000);
  TEST_ASSERT_FALSE(tdc.hasTimerPassed(1100, 300));
  TEST_ASSERT_TRUE(tdc.hasTimerPassed(1500, 300));
}

void test_pointer() {
  int i = 15;
  TEST_ASSERT_EQUAL(15, tdc.getTestPtr(&i));
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
  RUN_TEST(test_child_brightness_setting_is_changed);
  RUN_TEST(test_pointer);

  UNITY_END();
}

#endif
