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

  SD.remove(fileNameOfTestFile);
}
