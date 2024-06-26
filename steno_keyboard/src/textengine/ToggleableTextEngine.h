#pragma once
#include "TextEngine.h"

class ToggleableTextEngine : public TextEngine {
private:
  Text* text = NULL;
  uint32_t numberOfProcessedTexts = 0;
  bool outputtedKeyEventForCurrentText = false;
  const uint8_t keyCodeForLink = 32;
  bool skippingLink = false;

public:
  void process(Text* text);

  bool hasNext();

  KeyEvent next();
};
