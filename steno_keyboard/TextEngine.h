#pragma once

#include "Arduino.h"

class TextEngine {
public:
  virtual void setupBeforeText() = 0;

  virtual void process(uint8_t byte) = 0;

  virtual bool hasNext() = 0;

  virtual uint8_t next() = 0;

  virtual void cleanupAfterText() = 0;
};
