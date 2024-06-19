#pragma once
#include <Arduino.h>

enum class PressType : uint8_t { Press,
                                 Print,
                                 PressAndReleaseAll };

struct KeyEvent {
  const uint8_t keyCode;
  const PressType pressType;

  KeyEvent(uint8_t keyCode, PressType pressType);
};
