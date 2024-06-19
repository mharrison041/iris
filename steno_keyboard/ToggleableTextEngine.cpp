#include "ToggleableTextEngine.h"

void ToggleableTextEngine::process(Text *text) {
  this->text = text;
  if (text->hasNext()) {
    text->next();
    text->next();
    numberOfProcessedTexts++;
    numberOfProcessedBytesForCurrentText = 0;
  }
}

bool ToggleableTextEngine::hasNext() {
  return text->hasNext();
}

KeyEvent ToggleableTextEngine::next() {
  if (numberOfProcessedTexts > 1 && numberOfProcessedBytesForCurrentText == 0) {
    numberOfProcessedBytesForCurrentText++;
    return KeyEvent(keyCodeForLink, PressType::Print);
  } else {
    return KeyEvent(text->next(), PressType::Print);
  }
}
