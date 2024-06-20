#pragma once
#include <Arduino.h>

class Text {
public:
  virtual bool hasNext() = 0;

  virtual uint8_t next() = 0;
};