#pragma once
#include "testing.h"
#include "../src/text/SDCardText.h"

void testSDCardText() {
  connectToPC();
  testSuite("SDCardTextTest");
  if (!connectToSDCard()) {
    return;
  }

  char nameOfTestFile[] = "test";
  File testFile = SD.open(nameOfTestFile, FILE_WRITE);
  testFile.write("abcdefghijklmnopqrstuvwxyz");
  testFile.close();

  test("hasNext_returnsFalse_whenInitialPositionIsEqualToFinalPosition");
  {
    uint32_t initialPosition = 0;
    uint32_t finalPosition = 0;
    File testFile = SD.open(nameOfTestFile);
    SDCardText text(initialPosition, finalPosition, testFile);

    assertFalse(text.hasNext());

    testFile.close();
  }

  test("hasNext_returnsFalse_whenInitialPositionIsGreaterThanFinalPosition");
  {
    uint32_t initialPosition = 1;
    uint32_t finalPosition = 0;
    File testFile = SD.open(nameOfTestFile);
    SDCardText text(initialPosition, finalPosition, testFile);

    assertFalse(text.hasNext());

    testFile.close();
  }

  test("hasNext_returnsFalse_whenInitialPositionIsEqualToSizeOfFile");
  {
    File testFile = SD.open(nameOfTestFile);
    uint32_t initialPosition = testFile.size();
    uint32_t finalPosition = initialPosition + 1;
    SDCardText text(initialPosition, finalPosition, testFile);

    assertFalse(text.hasNext());

    testFile.close();
  }

  test("hasNext_returnsFalse_whenInitialPositionIsGreaterThanSizeOfFile");
  {
    File testFile = SD.open(nameOfTestFile);
    uint32_t initialPosition = testFile.size() + 1;
    uint32_t finalPosition = initialPosition + 1;
    SDCardText text(initialPosition, finalPosition, testFile);

    assertFalse(text.hasNext());

    testFile.close();
  }

  test("hasNext_returnsFalse_whenLastByteOfTextRangeHasBeenRead");
  {
    uint32_t initialPosition = 1;
    uint32_t finalPosition = 0;
    File testFile = SD.open(nameOfTestFile);
    SDCardText text(initialPosition, finalPosition, testFile);

    (void)text.next();

    assertFalse(text.hasNext());

    testFile.close();
  }

  test("hasNext_returnsTrue_whenInitialPositionIsLessThanFinalPosition");
  {
    uint32_t initialPosition = 0;
    uint32_t finalPosition = 1;
    File testFile = SD.open(nameOfTestFile);
    SDCardText text(initialPosition, finalPosition, testFile);

    assertTrue(text.hasNext());

    testFile.close();
  }

  test("next_returnsFirstByteOfTextRange_whenInitiallyCalled");
  {
    uint32_t initialPosition = 0;
    uint32_t finalPosition = 1;
    File testFile = SD.open(nameOfTestFile);
    SDCardText text(initialPosition, finalPosition, testFile);

    uint8_t expectedByte = 'a';
    uint8_t actualByte = text.next();
    assertTrue(expectedByte == actualByte);

    testFile.close();
  }

  test("next_returnsSecondByteOfTextRange_whenCalledTwice");
  {
    uint32_t initialPosition = 0;
    uint32_t finalPosition = 1;
    File testFile = SD.open(nameOfTestFile);
    SDCardText text(initialPosition, finalPosition, testFile);

    (void)text.next();

    uint8_t expectedByte = 'b';
    uint8_t actualByte = text.next();
    assertTrue(expectedByte == actualByte);

    testFile.close();
  }

  SD.remove(nameOfTestFile);
}
