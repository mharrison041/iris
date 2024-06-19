#pragma once
#include "TextEngine.h"

class ToggleableTextEngine : public TextEngine {
public:
  void process(Text* text);

  bool hasNext();

  KeyEvent next();
};
