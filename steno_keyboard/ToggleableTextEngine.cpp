#include "ToggleableTextEngine.h"

void ToggleableTextEngine::process(Text *text) {
  this->text = text;
  text->next();
  text->next();
  numberOfProcessedTexts++;
  numberOfProcessedBytesForCurrentText = 0;
}

bool ToggleableTextEngine::hasNext() {
  if (numberOfProcessedTexts > 1 && numberOfProcessedBytesForCurrentText == 0) {
    numberOfProcessedBytesForCurrentText++;
    return true;
  } else {
    return text->hasNext();
  }
}

KeyEvent ToggleableTextEngine::next() {
  return KeyEvent(text->next(), PressType::Print);
}
