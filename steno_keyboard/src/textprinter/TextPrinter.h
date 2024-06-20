#pragma once
#include "../text/Text.h"

class TextPrinter {
public:
  virtual void print(Text* text) = 0;
};
