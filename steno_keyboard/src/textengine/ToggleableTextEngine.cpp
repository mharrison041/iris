#include "ToggleableTextEngine.h"

void ToggleableTextEngine::process(Text *text) {
  this->text = text;
  if (text->hasNext()) {
    (void)text->next();
    (void)text->next();
    numberOfProcessedTexts++;  // bug: an overflow that results in a text not being properly linked to its preceding text; however, assuming normal use, this would requires a user to chord for about 76 years without restarting their device for this to occur
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
