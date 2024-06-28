#include "testing.h"
#include "../src/keyscanner/KeyScanner.h"
#include "../src/chordscanner/EveryKeyUpChordScanner.h"
#include "../src/dictionary/SDCardDictionary.h"
#include "../src/textengine/ToggleableTextEngine.h"
#include "../src/textprinter/ArduinoKeyboardTextPrinter.h"
#include "../src/mode/StenoMode.h"

/*
  If "HELLO WORLD!" is automatically typed, then the test has passed.
*/
void testStenoMode() {
  connectToPC();

  testSuite("StenoMode");
  const size_t numberOfKeys = 23;
  const size_t numberOfChords = 3;

  const size_t numberOfBytesToEncodeKeys = (numberOfKeys % 8 == 0) ? numberOfKeys / 8 : (numberOfKeys / 8) + 1;
  const size_t numberOfChordsAndReleases = 2 * numberOfChords;

  class KeyScannerFake : public KeyScanner {
  private:
    uint8_t counter = 0;
    uint8_t keyStates[numberOfChordsAndReleases][numberOfBytesToEncodeKeys] = {
      { 0, 0, 1 },
      { 0, 0, 0 },
      { 0, 0, 2 },
      { 0, 0, 0 },
      { 0, 0, 3 },
      { 0, 0, 0 }
    };

  public:
    void read(uint8_t keys[]) {
      memcpy(&keys[0], &keyStates[counter][0], numberOfBytesToEncodeKeys);
      counter = (counter + 1) % numberOfChordsAndReleases;
    }
  };

  // connect to SD card
  uint8_t slaveSelectPin = 4;
  if (!SD.begin(slaveSelectPin)) {
    Serial.println("    Failed to connect to SD card");
    return;
  }

  // write test file
  char fileName[] = "test";
  File file = SD.open(fileName, FILE_WRITE);
  uint8_t data[58] = { 0, 0, 0, 23,  // number of keys
                       0, 0, 0, 3,   // number of steno entries

                       0, 0, 1,      // first steno
                       0, 0, 0, 41,  // initial index of first text
                       0, 0, 0, 48,  // final index of first text

                       0, 0, 2,      // second steno
                       0, 0, 0, 48,  // initial index of second text
                       0, 0, 0, 55,  // final index of second text

                       0, 0, 3,      // third steno
                       0, 0, 0, 55,  // initial index of third text
                       0, 0, 0, 58,  // final index of third text

                       0, 0, 72, 69, 76, 76, 79,  // first text
                       0, 0, 87, 79, 82, 76, 68,  // second text
                       0, 2, 33 };                // third text

  file.write(data, sizeof(data));
  file.close();

  // instantiate steno mode
  KeyScannerFake keyScanner;
  EveryKeyUpChordScanner chordScanner(numberOfKeys);
  SDCardDictionary dictionary(fileName);
  ToggleableTextEngine textEngine;
  ArduinoKeyboardTextPrinter textPrinter(&textEngine);
  StenoMode mode(numberOfKeys, &keyScanner, &chordScanner, &dictionary, &textPrinter);

  // simulate chords being pressed
  for (int i = 0; i < numberOfChordsAndReleases; i++) {
    mode.execute();
  }

  // cleanup
  SD.remove(fileName);
}
