#include "EveryKeyUpChordDetector.h"

void EveryKeyUpChordDetector::scan(const uint8_t keyStates[]) {
  keyWasPressed = keyIsPressed;
  keyIsPressed = false;
  
  for (size_t i = 0; i < NUMBER_OF_BYTES_FOR_KEY_STATES; i++) {
    if (keyStates[i] > 0) {
      keyIsPressed = true;
      break;
    }
  }
}

bool EveryKeyUpChordDetector::detectedChord() {
  return keyWasPressed && !keyIsPressed;
}

void EveryKeyUpChordDetector::get(uint8_t steno[]) {
}
