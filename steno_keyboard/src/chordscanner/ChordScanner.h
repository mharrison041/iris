#pragma once
#include <Arduino.h>

class ChordScanner {
public:
  virtual void scan(const uint8_t keys[]) = 0;

  virtual bool detectedChord() = 0;

  virtual void get(uint8_t steno[]) = 0;
};
