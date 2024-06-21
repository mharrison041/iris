#pragma once
#include "KeyScanner.h"

class KeyScannerFake {
private:
  uint8_t* keys = NULL;
  size_t numberOfKeys = 0;

public:
  KeyScannerFake(uint8_t keys[], size_t numberOfKeys);

  ~KeyScannerFake();

  void read(uint8_t keys[]);
};
