#pragma once
#include "TextEngine.h"

class ToggleableTextEngine : public TextEngine {
private:
  Text* text = NULL;

public:
  void process(Text* text);

  bool hasNext();

  KeyEvent next();
};
