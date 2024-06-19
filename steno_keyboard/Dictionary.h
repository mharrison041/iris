#pragma once
#include "Text.h"

class Dictionary {
public:
  virtual Text* getTextFor(uint8_t steno[]) = 0;
};
