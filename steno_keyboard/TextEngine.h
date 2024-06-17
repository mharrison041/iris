#pragma once

#include "Arduino.h"

class TextEngine {
public:
  void setupBeforeText();

  void process(uint8_t byte);

  bool hasNext();

  uint8_t next();

  void cleanupAfterText();
};
