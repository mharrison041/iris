#pragma once
#include <Arduino.h>
#include "../text/Text.h"
#include "../keyevent/KeyEvent.h"

class TextEngine {
public:
  virtual void process(Text* text) = 0;

  virtual bool hasNext() = 0;

  virtual KeyEvent next() = 0;
};
