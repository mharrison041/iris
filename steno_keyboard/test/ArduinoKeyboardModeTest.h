#include "testing.h"
#include "../src/dictionary/SDCardDictionary.h"
#include "../src/mode/ArduinoKeyboardMode.h"

void testArduinoKeyboardMode() {
  connectToPC();
  if (!connectToSDCard()) {
    return;
  }

  testSuite("ArduinoKeyboardMode");

  const size_t numberOfKeys = 23;
  const size_t numberOfKeysToPress = 12;

  const size_t numberOfBytesToEncodeKeys = (numberOfKeys % 8 == 0) ? numberOfKeys / 8 : (numberOfKeys / 8) + 1;

  class KeyScannerFake : public KeyScanner {
  private:
    uint8_t counter = 0;
    uint8_t keyStates[numberOfKeysToPress + 1][numberOfBytesToEncodeKeys] = {
      { 0, 0, 1 },
      { 0, 0, 2 },
      { 0, 0, 4 },
      { 0, 0, 4 },
      { 0, 0, 8 },
      { 0, 0, 16 },
      { 0, 0, 32 },
      { 0, 0, 8 },
      { 0, 0, 64 },
      { 0, 0, 4 },
      { 0, 0, 128 },
      { 0, 1, 0 },
      { 0, 0, 0 }
    };

  public:
    void read(uint8_t keys[]) {
      memcpy(&keys[0], &keyStates[counter][0], numberOfBytesToEncodeKeys);
      counter = (counter + 1) % (numberOfKeysToPress + 1);
    }
  };

  // write test file
  char fileName[] = "test";
  File file = SD.open(fileName, FILE_WRITE);
  uint8_t data[116] = { 0, 0, 0, 23,  // number of keys
                        0, 0, 0, 9,   // number of key entries

                        0, 0, 1,       // first key
                        0, 0, 0, 107,  // initial index of first key code
                        0, 0, 0, 108,  // final index of first key code

                        0, 0, 2,       // second key
                        0, 0, 0, 108,  // initial index of second key code
                        0, 0, 0, 109,  // final index of second key code

                        0, 0, 4,       // third key
                        0, 0, 0, 109,  // initial index of third key code
                        0, 0, 0, 110,  // final index of third key code

                        0, 0, 8,
                        0, 0, 0, 110,
                        0, 0, 0, 111,

                        0, 0, 16,
                        0, 0, 0, 111,
                        0, 0, 0, 112,

                        0, 0, 32,
                        0, 0, 0, 112,
                        0, 0, 0, 113,

                        0, 0, 64,
                        0, 0, 0, 113,
                        0, 0, 0, 114,

                        0, 0, 128,
                        0, 0, 0, 114,
                        0, 0, 0, 115,

                        0, 1, 0,
                        0, 0, 0, 115,
                        0, 0, 0, 116,

                        72, 69, 76, 79, 32, 87, 82, 68, 33 };

  file.write(data, sizeof(data));
  file.close();

  // instantiate arduino keyboard mode
  KeyScannerFake keyScanner;
  SDCardDictionary dictionary(fileName);
  ArduinoKeyboardMode keyboardMode(numberOfKeys, &keyScanner, &dictionary);

  // simulate keys being pressed
  for (int i = 0; i < (numberOfKeysToPress + 1); i++) {
    keyboardMode.execute();
  }

  // cleanup
  SD.remove(fileName);
}
