#include <SPI.h>
#include <SD.h>

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

class Dictionary {
public:
  virtual bool open() = 0;

  virtual void close() = 0;

  virtual bool seekTextFor(uint8_t steno[]) = 0;

  virtual bool hasNext() = 0;

  virtual uint8_t next() = 0;
};

// Functions for testing
void testSuite(char testSuiteName[]) {
  Serial.println(testSuiteName);
}

void test(char testName[]) {
  Serial.print("    ");
  Serial.println(testName);
}

void assertTrue(bool value) {
  Serial.print("    - ");
  if (value == true) {
    Serial.println("Passed");
  } else {
    Serial.println("Failed");
  }
  Serial.print("\n");
}

void assertFalse(bool value) {
  assertTrue(!value);
}
