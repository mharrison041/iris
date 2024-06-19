#pragma once
#include "Text.h"

class TextPrinter {
public:
  virtual void print(Text* text) = 0;
};
