#include "testing.h"
#include "TextEngine.h"
#include "ToggleableTextEngine.h"

class TextFake : public Text {
private:
  static const size_t NUMBER_OF_BYTES_FOR_TEXT = 3;
  uint8_t bytes[NUMBER_OF_BYTES_FOR_TEXT] = { 0 };
  size_t counter = 0;

public:
  TextFake(uint8_t textEngineMetaData, uint8_t textMetaData, uint8_t text) {
    bytes[0] = textEngineMetaData;
    bytes[1] = textMetaData;
    bytes[2] = text;
  }

  TextFake() {
    counter = NUMBER_OF_BYTES_FOR_TEXT;
  }

  bool hasNext() {
    return counter < NUMBER_OF_BYTES_FOR_TEXT;
  }

  uint8_t next() {
    return bytes[counter++];
  }
};

void testToggleableTextEngine() {
  testSuite("ToggleableTextEngine");

  test("initialize");
  {
    TextEngine* textEngine = &ToggleableTextEngine();
    assertTrue(true);
  }

  test("hasNext_returnsFalse_whenTextIsEmpty");
  {
    TextFake text;
    ToggleableTextEngine textEngine;

    textEngine.process(&text);

    assertFalse(textEngine.hasNext());
  }
}
