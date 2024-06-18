#include "testing.h"
#include "SDCardText.h"

void testSDCardText() {
  testSuite("SDCardText");

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

  test("hasNext_returnsTrue_whenInitialPositionIsLessThanFinalPosition");
  {
    uint32_t initialPosition = 0;
    uint32_t finalPosition = 1;
    File testFile = SD.open(fileNameOfTestFile);
    SDCardText text(initialPosition, finalPosition, testFile);

    assertTrue(text.hasNext());

    testFile.close();
  }

  SD.remove(fileNameOfTestFile);
}
