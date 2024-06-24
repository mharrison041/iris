#pragma once
#include "src/chordscanner/ChordScanner.h"
#include "src/dictionary/Dictionary.h"
#include "src/keyscanner/KeyScanner.h"
#include "src/textprinter/TextPrinter.h"
#include "Mode.h"

class StenoMode : public Mode {
private:
  size_t numberOfBytesToEncodeKeys;
  KeyScanner* keyScanner;
  ChordScanner* chordScanner;
  Dictionary* dictionary;
  TextPrinter* textPrinter;

public:
  StenoMode(size_t numberOfKeys, KeyScanner* keyScanner, ChordScanner* chordScanner, Dictionary* dictionary, TextPrinter* textPrinter);

  void execute();
};
