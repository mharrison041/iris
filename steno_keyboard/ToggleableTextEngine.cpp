#include "ToggleableTextEngine.h"

void ToggleableTextEngine::process(Text *text) {
  this->text = text;
  text->next();
  text->next();
}

bool ToggleableTextEngine::hasNext() {
  return text->hasNext();
}

KeyEvent ToggleableTextEngine::next() {
  return KeyEvent(text->next(), PressType::Print);
}
