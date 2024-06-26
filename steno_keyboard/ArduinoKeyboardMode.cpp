#include "ArduinoKeyboardMode.h"

ArduinoKeyboardMode::ArduinoKeyboardMode(size_t numberOfKeys, KeyScanner* keyScanner, Dictionary* dictionary) {
  numberOfBytesToEncodeKeys = (numberOfKeys % 8 == 0) ? numberOfKeys / 8 : (numberOfKeys / 8) + 1;
  this->keyScanner = keyScanner;
  this->dictionary = dictionary;
}

void ArduinoKeyboardMode::execute() {
  uint8_t keys[numberOfBytesToEncodeKeys] = { 0 };
  keyScanner->read(keys);

  Text* text = dictionary->getTextFor(keys);
  while (text->hasNext()) {
    Keyboard.print((char)text->next());
  }

  delete text;
}
