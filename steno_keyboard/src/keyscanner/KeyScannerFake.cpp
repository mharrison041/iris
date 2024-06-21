#include "KeyScannerFake.h"

KeyScannerFake::KeyScannerFake(size_t numberOfKeys, size_t maxNumberOfKeyStates) {
  this->numberOfKeys = numberOfKeys;
  this->maxNumberOfKeyStates = maxNumberOfKeyStates;
  keyStates = new uint8_t[numberOfKeys * maxNumberOfKeyStates]{ 0 };
}

KeyScannerFake::~KeyScannerFake() {
  delete[] keyStates;
}

void KeyScannerFake::add(const uint8_t keys[]) {
  if(addingIndex == maxNumberOfKeyStates) {
    addingIndex = 0;
  }

  memcpy(&keyStates[addingIndex * numberOfKeys], &keys[0], numberOfKeys);
  addingIndex++;
}

void KeyScannerFake::read(uint8_t keys[]) {
  if(readingIndex == maxNumberOfKeyStates) {
    readingIndex = 0;
  }

  memcpy(&keys[0], &keyStates[readingIndex * numberOfKeys], numberOfKeys);
  readingIndex++;
}
