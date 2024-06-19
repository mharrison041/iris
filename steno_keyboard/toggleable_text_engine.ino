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

  test("hasNext_returnsTrue_whenTextIsNotEmpty");
  {
    uint8_t textEngineMetaData = 0;
    uint8_t textMetaData = 0;
    uint8_t textData = 122;
    TextFake text(textEngineMetaData, textMetaData, textData);
    ToggleableTextEngine textEngine;

    textEngine.process(&text);

    assertTrue(textEngine.hasNext());
  }

  test("hasNext_returnsFalse_whenTextHasBeenCompletelyProcessed");
  {
    uint8_t textEngineMetaData = 0;
    uint8_t textMetaData = 0;
    uint8_t textData = 122;
    TextFake text(textEngineMetaData, textMetaData, textData);
    ToggleableTextEngine textEngine;

    textEngine.process(&text);
    (void)textEngine.next();

    assertFalse(textEngine.hasNext());
  }

  test("next_returnsFirstByteOfTextAsPrintKeyEvent_whenInitiallyCalledWhileProcessingTextLiteral");
  {
    uint8_t textEngineMetaData = 0;
    uint8_t textMetaData = 0;
    uint8_t textData = 122;
    TextFake text(textEngineMetaData, textMetaData, textData);
    ToggleableTextEngine textEngine;

    textEngine.process(&text);

    KeyEvent expectedKeyEvent(122, PressType::Print);
    KeyEvent actualKeyEvent = textEngine.next();

    assertTrue(expectedKeyEvent.keyCode == actualKeyEvent.keyCode
               && expectedKeyEvent.pressType == actualKeyEvent.pressType);
  }

  test("hasNext_returnsTrue_whenCalledOneTimeMoreThanLengthOfTextWhileProcessingSecondTextLiteral");
  {
    uint8_t textEngineMetaData = 0;
    uint8_t textMetaData = 0;
    uint8_t textData = 122;
    TextFake text(textEngineMetaData, textMetaData, textData);
    uint8_t otherTextEngineMetaData = 0;
    uint8_t otherTextMetaData = 0;
    uint8_t otherTextData = 97;
    TextFake otherText(otherTextEngineMetaData, otherTextMetaData, otherTextData);
    ToggleableTextEngine textEngine;

    textEngine.process(&text);
    (void)textEngine.next();
    textEngine.process(&otherText);
    (void)textEngine.next();

    assertTrue(textEngine.hasNext());
  }
}
