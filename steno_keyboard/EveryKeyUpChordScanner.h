#pragma once

#include <Arduino.h>

#include "ChordScanner.h"

class EveryKeyUpChordScanner : public ChordScanner {
private:
  const static size_t NUMBER_OF_BYTES_FOR_KEYS = 3;

  bool keyWasPressed = false;
  bool keyIsPressed = false;
  uint8_t historyOfPressedKeyStates[NUMBER_OF_BYTES_FOR_KEYS] = { 0 };

public:
  void scan(const uint8_t keys[]);

  bool detectedChord();

  void get(uint8_t steno[]);
};
