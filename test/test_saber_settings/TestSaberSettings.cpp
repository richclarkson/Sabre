#ifdef UNIT_TEST

#include "StateManager.h"
#include <unity.h>

StateManager sm;

void setUp() {
    sm = StateManager();
}

void test_settings_exist() {
    Serial.begin(9600);
    Serial.print("Channel: ");
    Serial.println(sm.getChannel());
    Serial.print("Sensitivity: ");
    Serial.println(sm.getSensitivity());
    Serial.print("Brightness: ");
    Serial.println(sm.getBrightness());
}

int main() {
  UNITY_BEGIN();

  RUN_TEST(test_settings_exist);

  UNITY_END();
}

#endif
