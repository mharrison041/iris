#pragma once
#include "testing.h"
#include "../src/textengine/ToggleableTextEngine.h"

void testToggleableTextEngine() {
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

  class LongTextFake : public Text {
  private:
    static const size_t NUMBER_OF_BYTES_FOR_TEXT = 4;
    uint8_t bytes[NUMBER_OF_BYTES_FOR_TEXT] = { 0 };
    size_t counter = 0;

  public:
    LongTextFake(uint8_t textEngineMetaData, uint8_t textMetaData, uint8_t firstByte, uint8_t secondByte) {
      bytes[0] = textEngineMetaData;
      bytes[1] = textMetaData;
      bytes[2] = firstByte;
      bytes[3] = secondByte;
    }

    bool hasNext() {
      return counter < NUMBER_OF_BYTES_FOR_TEXT;
    }

    uint8_t next() {
      return bytes[counter++];
    }
  };

  connectToPC();
  testSuite("ToggleableTextEngineTest");

  uint8_t textEngineMetaData = 0;
  uint8_t textMetaData = 0;
  uint8_t textData = 122;

  uint8_t otherTextEngineMetaData = 0;
  uint8_t otherTextMetaData = 0;
  uint8_t otherTextData = 97;

  test("hasNext_returnsFalse_whenTextIsEmpty");
  {
    TextFake text;
    ToggleableTextEngine textEngine;

    textEngine.process(&text);

    assertFalse(textEngine.hasNext());
  }

  test("hasNext_returnsTrue_whenTextIsNotEmpty");
  {
    TextFake text(textEngineMetaData, textMetaData, textData);
    ToggleableTextEngine textEngine;

    textEngine.process(&text);

    assertTrue(textEngine.hasNext());
  }

  test("hasNext_returnsFalse_whenTextHasBeenCompletelyProcessed");
  {
    TextFake text(textEngineMetaData, textMetaData, textData);
    ToggleableTextEngine textEngine;

    textEngine.process(&text);
    (void)textEngine.next();

    assertFalse(textEngine.hasNext());
  }

  test("next_returnsFirstByteOfTextAsPrintKeyEvent_whenInitiallyCalledWhileProcessingTextLiteral");
  {
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
    TextFake text(textEngineMetaData, textMetaData, textData);
    TextFake otherText(otherTextEngineMetaData, otherTextMetaData, otherTextData);
    ToggleableTextEngine textEngine;

    textEngine.process(&text);
    (void)textEngine.next();
    textEngine.process(&otherText);
    (void)textEngine.next();

    assertTrue(textEngine.hasNext());
  }

  test("hasNext_returnsFalse_whenProcessingSecondTextThatIsEmpty");
  {
    TextFake text(textEngineMetaData, textMetaData, textData);
    TextFake emptyText;
    ToggleableTextEngine textEngine;

    textEngine.process(&text);
    (void)textEngine.next();
    textEngine.process(&emptyText);

    assertFalse(textEngine.hasNext());
  }

  test("hasNext_returnsFalse_whenCalledOneTimeMoreThanLengthOfTextWhileProcessingSecondTextLiteralIfFirstTextWasEmpty");
  {
    TextFake emptyText;
    TextFake otherText(otherTextEngineMetaData, otherTextMetaData, otherTextData);
    ToggleableTextEngine textEngine;

    textEngine.process(&emptyText);
    (void)textEngine.next();
    textEngine.process(&otherText);
    (void)textEngine.next();

    assertFalse(textEngine.hasNext());
  }

  test("next_returnsPrintKeyEventWithWhiteSpace_whenInitiallyCalledWhileProcessingSecondTextLiteral");
  {
    TextFake text(textEngineMetaData, textMetaData, textData);
    TextFake otherText(otherTextEngineMetaData, otherTextMetaData, otherTextData);
    ToggleableTextEngine textEngine;

    textEngine.process(&text);
    (void)textEngine.next();
    textEngine.process(&otherText);

    KeyEvent expectedKeyEvent(32, PressType::Print);
    KeyEvent actualKeyEvent = textEngine.next();

    assertTrue(expectedKeyEvent.keyCode == actualKeyEvent.keyCode
               && expectedKeyEvent.pressType == actualKeyEvent.pressType);
  }

  test("next_returnsPrintKeyEventWithFirstKeyCodeOfText_whenCalledTwiceWhileProcessingSecondTextLiteral");
  {
    TextFake text(textEngineMetaData, textMetaData, textData);
    TextFake otherText(otherTextEngineMetaData, otherTextMetaData, otherTextData);
    ToggleableTextEngine textEngine;

    textEngine.process(&text);
    (void)textEngine.next();
    textEngine.process(&otherText);
    (void)textEngine.next();

    KeyEvent expectedKeyEvent(otherTextData, PressType::Print);
    KeyEvent actualKeyEvent = textEngine.next();

    assertTrue(expectedKeyEvent.keyCode == actualKeyEvent.keyCode
               && expectedKeyEvent.pressType == actualKeyEvent.pressType);
  }

  test("hasNext_returnsFalse_whenAllKeyCodesOfSecondTextHaveBeenRead");
  {
    TextFake text(textEngineMetaData, textMetaData, textData);
    TextFake otherText(otherTextEngineMetaData, otherTextMetaData, otherTextData);
    ToggleableTextEngine textEngine;

    textEngine.process(&text);
    (void)textEngine.next();
    textEngine.process(&otherText);
    (void)textEngine.next();
    (void)textEngine.next();

    assertFalse(textEngine.hasNext());
  }

  test("hasNext_returnsTrue_whenOnlyFirstByteOfLongTextHasBeenRead");
  {
    uint8_t firstByte = 98;
    uint8_t secondByte = 99;
    LongTextFake text(textEngineMetaData, textMetaData, firstByte, secondByte);
    ToggleableTextEngine textEngine;

    textEngine.process(&text);
    (void)textEngine.next();

    assertTrue(textEngine.hasNext());
  }

  test("next_returnsPrintKeyEventWithSecondByteOfLongText_whenCalledTwice");
  {
    uint8_t firstByte = 98;
    uint8_t secondByte = 99;
    LongTextFake text(textEngineMetaData, textMetaData, firstByte, secondByte);
    ToggleableTextEngine textEngine;

    textEngine.process(&text);
    (void)textEngine.next();

    KeyEvent expectedKeyEvent(secondByte, PressType::Print);
    KeyEvent actualKeyEvent = textEngine.next();
    assertTrue(expectedKeyEvent.keyCode == actualKeyEvent.keyCode
               && expectedKeyEvent.pressType == actualKeyEvent.pressType);
  }

  test("next_returnsPrintEventWithFirstByteOfSecondText_whenFirstTextIgnoresFollowingLink");
  {
    uint8_t textMetaData = 1;
    TextFake text(textEngineMetaData, textMetaData, textData);
    TextFake otherText(otherTextEngineMetaData, otherTextMetaData, otherTextData);
    ToggleableTextEngine textEngine;

    textEngine.process(&text);
    (void)textEngine.next();
    textEngine.process(&otherText);

    KeyEvent expectedKeyEvent(otherTextData, PressType::Print);
    KeyEvent actualKeyEvent = textEngine.next();
    assertTrue(expectedKeyEvent.keyCode == actualKeyEvent.keyCode
               && expectedKeyEvent.pressType == actualKeyEvent.pressType);
  }

  test("next_returnsPrintEventWithWhitespace_whenInitiallyProcessingThirdTextAfterFirstTextIgnoredFollowingLink");
  {
    uint8_t textMetaData = 1;
    TextFake firstText(textEngineMetaData, textMetaData, textData);
    TextFake secondText(otherTextEngineMetaData, otherTextMetaData, otherTextData);
    TextFake thirdText(otherTextEngineMetaData, otherTextMetaData, otherTextData);
    ToggleableTextEngine textEngine;

    textEngine.process(&firstText);
    (void)textEngine.next();
    textEngine.process(&secondText);
    (void)textEngine.next();
    textEngine.process(&thirdText);

    uint8_t asciiForWhitespace = 32;
    KeyEvent expectedKeyEvent(asciiForWhitespace, PressType::Print);
    KeyEvent actualKeyEvent = textEngine.next();
    assertTrue(expectedKeyEvent.keyCode == actualKeyEvent.keyCode
               && expectedKeyEvent.pressType == actualKeyEvent.pressType);
  }

  test("next_returnsPrintEventWithFirstByteOfSecondText_whenSecondTextIgnoresPrecedingLink");
  {
    uint8_t otherTextMetaData = 2;
    TextFake text(textEngineMetaData, textMetaData, textData);
    TextFake otherText(otherTextEngineMetaData, otherTextMetaData, otherTextData);
    ToggleableTextEngine textEngine;

    textEngine.process(&text);
    (void)textEngine.next();
    textEngine.process(&otherText);

    KeyEvent expectedKeyEvent(otherTextData, PressType::Print);
    KeyEvent actualKeyEvent = textEngine.next();
    assertTrue(expectedKeyEvent.keyCode == actualKeyEvent.keyCode
               && expectedKeyEvent.pressType == actualKeyEvent.pressType);
  }

  test("next_returnsPrintEventWithWhitespace_whenInitiallyProcessingThirdTextAfterSecondTextIgnoredPrecedingLink");
  {
    uint8_t otherTextMetaData = 2;
    TextFake firstText(textEngineMetaData, textMetaData, textData);
    TextFake secondText(otherTextEngineMetaData, otherTextMetaData, otherTextData);
    TextFake thirdText(otherTextEngineMetaData, textMetaData, otherTextData);
    ToggleableTextEngine textEngine;

    textEngine.process(&firstText);
    (void)textEngine.next();
    textEngine.process(&secondText);
    (void)textEngine.next();
    textEngine.process(&thirdText);

    uint8_t asciiForWhitespace = 32;
    KeyEvent expectedKeyEvent(asciiForWhitespace, PressType::Print);
    KeyEvent actualKeyEvent = textEngine.next();
    assertTrue(expectedKeyEvent.keyCode == actualKeyEvent.keyCode
               && expectedKeyEvent.pressType == actualKeyEvent.pressType);
  }
}
