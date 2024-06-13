#include "EveryKeyUpChordDetector.h"

void EveryKeyUpChordDetector::scan(const uint8_t keyStates[]) {
  bool detectedChordDuringLastScan = detectedChord();
  if (detectedChordDuringLastScan) {
    memset(historyOfPressedKeyStates, 0, NUMBER_OF_BYTES_FOR_KEY_STATES);
  }

  keyWasPressed = keyIsPressed;
  keyIsPressed = false;

  for (size_t i = 0; i < NUMBER_OF_BYTES_FOR_KEY_STATES; i++) {
    historyOfPressedKeyStates[i] |= keyStates[i];
    if (keyStates[i] > 0) {
      keyIsPressed = true;
    }
  }
}

bool EveryKeyUpChordDetector::detectedChord() {
  return keyWasPressed && !keyIsPressed;
}

void EveryKeyUpChordDetector::get(uint8_t steno[]) {
  for (size_t i = 0; i < NUMBER_OF_BYTES_FOR_KEY_STATES; i++) {
    steno[i] = historyOfPressedKeyStates[i];
  }
}
