#pragma once

class ChordDetector {
public:
  virtual void scan(uint8_t keyStates[]) = 0;

  virtual bool detectedChord() = 0;

  virtual void get(uint8_t chord[]) = 0;
};
