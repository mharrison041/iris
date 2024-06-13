#pragma once

#include <Arduino.h>

#include "ChordDetector.h"

class EveryKeyUpChordDetector : public ChordDetector {
private:
  const static size_t NUMBER_OF_BYTES_FOR_KEY_STATES = 3;

  bool keyWasPressed = false;
  bool keyIsPressed = false;
  uint8_t historyOfPressedKeyStates[NUMBER_OF_BYTES_FOR_KEY_STATES] = { 0 };

public:
  void scan(const uint8_t keyStates[]);

  bool detectedChord();

  void get(uint8_t steno[]);
};
