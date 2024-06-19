#pragma once
#include "TextEngine.h"

class ToggleableTextEngine : public TextEngine {
private:
  Text* text = NULL;
  uint32_t numberOfProcessedTexts = 0;
  uint32_t numberOfProcessedBytesForCurrentText = 0;

public:
  void process(Text* text);

  bool hasNext();

  KeyEvent next();
};
