#pragma once
#include "KeyScanner.h"

class KeyScannerFake {
private:
  uint8_t* keyStates = NULL;
  size_t addingIndex = 0;
  size_t readingIndex = 0;
  size_t numberOfKeys = 0;
  size_t maxNumberOfKeyStates = 0;

public:
  KeyScannerFake(size_t numberOfKeys, size_t maxNumberOfKeyStates);

  ~KeyScannerFake();

  void add(const uint8_t keys[]);

  void read(uint8_t keys[]);
};
