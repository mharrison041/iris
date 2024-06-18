#include "testing.h"
#include "SDCardText.h"

void testSDCardText() {
  testSuite("SDCardText");

  uint8_t slaveSelectPin = 4;
  if (!SD.begin(slaveSelectPin)) {
    Serial.println("    Failed to connect to SD card");
    return;
  }

  char fileNameOfTestFile[] = "test";
  File testFile = SD.open(fileNameOfTestFile, FILE_WRITE);
  testFile.write("abcdefghijklmnopqrstuvwxyz");
  testFile.close();

  test("initialize");
  {
    uint32_t initialPosition = 0;
    uint32_t finalPosition = 3;
    File testFile = SD.open(fileNameOfTestFile);
    SDCardText text(initialPosition, finalPosition, testFile);
    testFile.close();
    assertTrue(true);
  }

  test("hasNext_returnsFalse_whenInitialPositionEqualsFinalPosition");
  {
    uint32_t initialPosition = 0;
    uint32_t finalPosition = 0;
    File testFile = SD.open(fileNameOfTestFile);
    SDCardText text(initialPosition, finalPosition, testFile);

    assertFalse(text.hasNext());

    testFile.close();
  }

  test("hasNext_returnsFalse_whenInitialPositionIsBiggerThanFinalPosition");
  {
    uint32_t initialPosition = 1;
    uint32_t finalPosition = 0;
    File testFile = SD.open(fileNameOfTestFile);
    SDCardText text(initialPosition, finalPosition, testFile);

    assertFalse(text.hasNext());

    testFile.close();
  }

  test("hasNext_returnsFalse_whenInitialPositionIsEqualToSizeOfFile");
  {
    File testFile = SD.open(fileNameOfTestFile);
    uint32_t initialPosition = testFile.size();
    uint32_t finalPosition = initialPosition + 1;
    SDCardText text(initialPosition, finalPosition, testFile);

    assertFalse(text.hasNext());

    testFile.close();
  }

  test("hasNext_returnsFalse_whenInitialPositionIsGreaterThanSizeOfFile");
  {
    File testFile = SD.open(fileNameOfTestFile);
    uint32_t initialPosition = testFile.size() + 1;
    uint32_t finalPosition = initialPosition + 1;
    SDCardText text(initialPosition, finalPosition, testFile);

    assertFalse(text.hasNext());

    testFile.close();
  }

  test("hasNext_returnsFalse_whenLastByteOfRangeHasBeenRead");
  {
    uint32_t initialPosition = 1;
    uint32_t finalPosition = 0;
    File testFile = SD.open(fileNameOfTestFile);
    SDCardText text(initialPosition, finalPosition, testFile);

    (void)text.next();

    assertFalse(text.hasNext());

    testFile.close();
  }

  test("hasNext_returnsTrue_whenInitialPositionIsLessThanFinalPosition");
  {
    uint32_t initialPosition = 0;
    uint32_t finalPosition = 1;
    File testFile = SD.open(fileNameOfTestFile);
    SDCardText text(initialPosition, finalPosition, testFile);

    assertTrue(text.hasNext());

    testFile.close();
  }

  test("next_returnsFirstByteOfRange_whenInitiallyCalled");
  {
    uint32_t initialPosition = 0;
    uint32_t finalPosition = 1;
    File testFile = SD.open(fileNameOfTestFile);
    SDCardText text(initialPosition, finalPosition, testFile);

    uint8_t expectedByte = 'a';
    uint8_t actualByte = text.next();
    assertTrue(expectedByte == actualByte);

    testFile.close();
  }

  test("next_returnsSecondByteOfRange_whenCalledTwice");
  {
    uint32_t initialPosition = 0;
    uint32_t finalPosition = 1;
    File testFile = SD.open(fileNameOfTestFile);
    SDCardText text(initialPosition, finalPosition, testFile);

    (void)text.next();

    uint8_t expectedByte = 'b';
    uint8_t actualByte = text.next();
    assertTrue(expectedByte == actualByte);

    testFile.close();
  }

  SD.remove(fileNameOfTestFile);
}
