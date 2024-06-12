#pragma once

#include <Arduino.h>

#include "ChordDetector.h"

class EveryKeyUpChordDetector : public ChordDetector {
public:
  void scan(const uint8_t keyStates[]);

  bool detectedChord();

  void get(uint8_t steno[]);
};
