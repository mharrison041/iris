#pragma once
#include "ChordScanner.h"

class EveryKeyUpChordScanner : public ChordScanner {
private:
  bool keyWasPressed = false;
  bool keyIsPressed = false;
  uint8_t numberOfBytesToEncodeKeys = 0;
  uint8_t* historyOfPressedKeyStates = NULL;

public:
  EveryKeyUpChordScanner(size_t numberOfKeys);

  ~EveryKeyUpChordScanner();

  void scan(const uint8_t keys[]);

  bool detectedChord();

  void get(uint8_t steno[]);
};
