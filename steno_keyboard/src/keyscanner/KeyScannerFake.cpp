#include "KeyScannerFake.h"

KeyScannerFake::KeyScannerFake(uint8_t keys[], size_t numberOfKeys) {
  this->keys = new uint8_t[numberOfKeys];
  this->numberOfKeys = numberOfKeys;
  memcpy(this->keys, &keys[0], numberOfKeys);
}

KeyScannerFake::~KeyScannerFake() {
  delete[] keys;
}

void KeyScannerFake::read(uint8_t keys[]) {
  memcpy(&keys[0], this->keys, numberOfKeys);
}
