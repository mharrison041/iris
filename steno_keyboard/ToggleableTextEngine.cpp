#include "ToggleableTextEngine.h"

void ToggleableTextEngine::process(Text *text) {
  this->text = text;
}

bool ToggleableTextEngine::hasNext() {
  return text->hasNext();
}

KeyEvent ToggleableTextEngine::next() {
}
