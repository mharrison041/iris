#pragma once
#include "Keyboard.h"
#include "src/dictionary/Dictionary.h"
#include "src/keyscanner/KeyScanner.h"
#include "Mode.h"

class ArduinoKeyboardMode : public Mode {
private:
  size_t numberOfBytesToEncodeKeys;
  KeyScanner* keyScanner;
  Dictionary* dictionary;

public:
  ArduinoKeyboardMode(size_t numberOfKeys, KeyScanner* keyScanner, Dictionary* dictionary);

  void execute();
};
