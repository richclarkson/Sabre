#ifndef TapPressButton_h  //guard - housekeeping, saying that if already included don't the rest of this code
#define TapPressButton_h

class TapPressButton {    //encapsulated code
public:   // interface - useable in main
  TapPressButton();
  TapPressButton(int tap_threshold, int tap_length, int press_threshold, int press_length);
  void update(bool input, unsigned long timerVal);
  bool isTap();
  bool isPress();

private:  // internal inner workings
  bool currentButtonState;
  bool prevButtonState;
  bool stateHasChanged();
  unsigned long TAP_THRESHOLD;
  unsigned long TAP_LENGTH;
  unsigned long PRESS_THRESHOLD;
  unsigned long PRESS_LENGTH;
  unsigned long tapTimer;
  unsigned long pressTimer;
  unsigned long prevTimerVal;
  bool isPressInTapWindow();
  bool isPressInPressWindow();
  void setStates(bool btnInput);
  void setPressType();
  char pressType;
  bool pressTypeIsTap();
  bool pressTypeIsPress();
  void setTimers(unsigned long timerVal);
  void setPressTimer(unsigned long TimerVal);
  void setTapTimer(unsigned long TimerVal);
};

#endif
