#include "EveryKeyUpChordScanner.h"

EveryKeyUpChordScanner::EveryKeyUpChordScanner(size_t numberOfKeys) {
  numberOfBytesToEncodeKeys = (numberOfKeys % 8 == 0) ? numberOfKeys / 8 : (numberOfKeys / 8) + 1;
  historyOfPressedKeyStates = new uint8_t[numberOfBytesToEncodeKeys]{ 0 };
}

EveryKeyUpChordScanner::~EveryKeyUpChordScanner() {
  delete[] historyOfPressedKeyStates;
}

void EveryKeyUpChordScanner::scan(const uint8_t keys[]) {
  bool detectedChordDuringLastScan = detectedChord();
  if (detectedChordDuringLastScan) {
    memset(historyOfPressedKeyStates, 0, numberOfBytesToEncodeKeys);
  }

  keyWasPressed = keyIsPressed;
  keyIsPressed = false;

  for (size_t i = 0; i < numberOfBytesToEncodeKeys; i++) {
    historyOfPressedKeyStates[i] |= keys[i];
    if (keys[i] > 0) {
      keyIsPressed = true;
    }
  }
}

bool EveryKeyUpChordScanner::detectedChord() {
  return keyWasPressed && !keyIsPressed;
}

void EveryKeyUpChordScanner::get(uint8_t steno[]) {
  for (size_t i = 0; i < numberOfBytesToEncodeKeys; i++) {
    steno[i] = historyOfPressedKeyStates[i];
  }
}
