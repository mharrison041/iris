#pragma once
#include <Arduino.h>

class KeyScanner {
public:
  virtual void read(uint8_t keys[]) = 0;
};
