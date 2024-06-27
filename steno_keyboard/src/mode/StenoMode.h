#pragma once
#include "../chordscanner/ChordScanner.h"
#include "../dictionary/Dictionary.h"
#include "../keyscanner/KeyScanner.h"
#include "../textprinter/TextPrinter.h"
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
