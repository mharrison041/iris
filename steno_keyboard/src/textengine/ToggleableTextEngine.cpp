#include "ToggleableTextEngine.h"

void ToggleableTextEngine::process(Text *text) {
  this->text = text;
  if (text->hasNext()) {
    (void)text->next();
    if(text->next() == 1) {
      skippingLink = true;
    }
    numberOfProcessedTexts++;  // bug: an integer overflow that results in a text not being properly linked to its preceding text; however, assuming normal use, this would require a user to chord for about 76 years without restarting their device for this to occur
    numberOfProcessedBytesForCurrentText = 0;
  }
}

bool ToggleableTextEngine::hasNext() {
  return text->hasNext();
}

KeyEvent ToggleableTextEngine::next() {
  if (numberOfProcessedTexts > 1 && numberOfProcessedBytesForCurrentText == 0) {
    if(skippingLink) {
      numberOfProcessedBytesForCurrentText++;
      return KeyEvent(text->next(), PressType::Print);
    } else {
      numberOfProcessedBytesForCurrentText++;
      return KeyEvent(keyCodeForLink, PressType::Print);
    }
  } else {
    return KeyEvent(text->next(), PressType::Print);
  }
}
