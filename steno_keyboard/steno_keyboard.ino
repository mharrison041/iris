#include <SPI.h>
#include <SD.h>

class SDCardDictionary;

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}

// Classes
class KeyScanner {
public:
  virtual void read(uint8_t keyStates[]) = 0;
};

class ChordDetector {
public:
  virtual void scan(uint8_t keyStates[]) = 0;

  virtual bool detectedChord() = 0;

  virtual void get(uint8_t chord[]) = 0;
};
