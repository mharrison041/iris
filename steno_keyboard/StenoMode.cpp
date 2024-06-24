#include "StenoMode.h"

StenoMode::StenoMode(size_t numberOfKeys, KeyScanner* keyScanner, ChordScanner* chordScanner, Dictionary* dictionary, TextPrinter* textPrinter) {
  numberOfBytesToEncodeKeys = (numberOfKeys % 8 == 0) ? numberOfKeys / 8 : (numberOfKeys / 8) + 1;
  this->keyScanner = keyScanner;
  this->chordScanner = chordScanner;
  this->dictionary = dictionary;
  this->textPrinter = textPrinter;
}

void StenoMode::execute() {
  uint8_t keys[numberOfBytesToEncodeKeys] = { 0 };
  keyScanner->read(keys);
  chordScanner->scan(keys);

  if (chordScanner->detectedChord()) {
    uint8_t steno[numberOfBytesToEncodeKeys] = { 0 };
    chordScanner->get(steno);

    Text* text = dictionary->getTextFor(steno);
    textPrinter->print(text);

    delete text;
  }
}
