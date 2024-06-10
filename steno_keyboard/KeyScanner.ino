#pragma once

class KeyScanner {
public:
  virtual void read(uint8_t keyStates[]) = 0;
};
