#include "EveryKeyUpChordScanner.h"

void EveryKeyUpChordScanner::scan(const uint8_t keys[]) {
  bool detectedChordDuringLastScan = detectedChord();
  if (detectedChordDuringLastScan) {
    memset(historyOfPressedKeyStates, 0, NUMBER_OF_BYTES_FOR_KEYS);
  }

  keyWasPressed = keyIsPressed;
  keyIsPressed = false;

  for (size_t i = 0; i < NUMBER_OF_BYTES_FOR_KEYS; i++) {
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
  for (size_t i = 0; i < NUMBER_OF_BYTES_FOR_KEYS; i++) {
    steno[i] = historyOfPressedKeyStates[i];
  }
}
