#ifdef UNIT_TEST

#include "StateManager.h"
#include "States.h"
#include <unity.h>

class TestDisplayController : public DisplayController {
  int testVal;

public:
  TestDisplayController() { testVal = 0; }
  int getTestVal() { return testVal; }
  void turnOff() { testVal = 0; }
  void displayFallingDot() {
    turnOff();
    testVal += 1;
  }
  void displayMiddleOut() {
    turnOff();
    testVal = 2;
  }
  void displayRipple() {
    turnOff();
    testVal = 3;
  }
  void displayBangAndFade() {
    turnOff();
    testVal = 4;
  }
  void displayRainbow() {
    turnOff();
    testVal = 5;
  }
};

StateManager sm;
TestDisplayController tdc;
unsigned long timerVal;

void setUp() {
  sm = StateManager(new NormalOff, new Neon);
  sm.registerDisplayController(&tdc);
}

void test_display_can_be_called_from_state_when_manager_updated() {
  timerVal = 0;
  sm.update(timerVal);
  TEST_ASSERT_EQUAL(0, tdc.getTestVal());
  sm.tap();
  sm.update(timerVal);
  TEST_ASSERT_EQUAL(1, tdc.getTestVal());
}

void test_states_call_displays_as_expected() {
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

int main() {
  UNITY_BEGIN();

  RUN_TEST(test_display_can_be_called_from_state_when_manager_updated);
  RUN_TEST(test_states_call_displays_as_expected);

  UNITY_END();
}

#endif
