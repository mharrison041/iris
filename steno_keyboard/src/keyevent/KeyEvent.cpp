#include "KeyEvent.h"

KeyEvent::KeyEvent(uint8_t keyCode, PressType pressType)
  : keyCode(keyCode), pressType(pressType) {}
