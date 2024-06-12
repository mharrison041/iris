#pragma once

class ChordDetector {
public:
  virtual void scan(const uint8_t keyStates[]) = 0;

  virtual bool detectedChord() = 0;

  virtual void get(uint8_t steno[]) = 0;
};
