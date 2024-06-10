#include "testing.h"

void testSDCardDictionary() {
  testSuite("SDCardDictionaryTest");

  uint8_t slaveSelectPin = 4;
  if (!SD.begin(slaveSelectPin)) {
    Serial.println("    Failed to connect to SD card");
    return;
  }

  char fileName[] = "test";
  File file = SD.open(fileName, FILE_WRITE);
  uint8_t data[30] = { 0, 0, 0, 2,   // number of steno entries
                       0, 0, 4,      // first steno
                       0, 0, 0, 26,  // initial index of first text
                       0, 0, 0, 28,  // final index of first text
                       0, 4, 0,      // second steno
                       0, 0, 0, 28,  // initial index of second text
                       0, 0, 0, 30,  // final index of second text
                       17, 50,       // first text
                       74, 25 };     // second text
  file.write(data, 30);
  file.close();

  uint8_t firstSteno[3] = { 0, 0, 4 };
  uint8_t secondSteno[3] = { 0, 4, 0 };
  uint8_t unknownSteno[3] = { 0, 1, 0 };
  SDCardDictionary dictionary(fileName);

  test("open_returnsFalse_whenFileDoesNotExist");
  {
    SDCardDictionary dictionary("void");

    assertFalse(dictionary.open());
  }

  test("open_returnsTrue_whenFileDoesExist");
  {
    assertTrue(dictionary.open());

    dictionary.close();
  }

  test("seekTextFor_returnsFalse_whenSeekingUnknownSteno");
  {
    dictionary.open();

    assertFalse(dictionary.seekTextFor(unknownSteno));

    dictionary.close();
  }

  test("seekTextFor_returnsTrue_whenSeekingFirstSteno");
  {
    dictionary.open();

    assertTrue(dictionary.seekTextFor(firstSteno));

    dictionary.close();
  }

  test("seekTextFor_returnsTrue_whenSeekingSecondSteno");
  {
    dictionary.open();

    assertTrue(dictionary.seekTextFor(secondSteno));

    dictionary.close();
  }

  test("next_returnsFirstByteFromFirstText_whenFirstCalled");
  {
    dictionary.open();
    dictionary.seekTextFor(firstSteno);

    assertTrue(dictionary.next() == 17);

    dictionary.close();
  }

  test("next_returnsFirstByteFromSecondText_whenFirstCalled");
  {
    dictionary.open();
    dictionary.seekTextFor(secondSteno);

    assertTrue(dictionary.next() == 74);

    dictionary.close();
  }

  test("next_returnsSecondByteFromText_whenCalledTwice");
  {
    dictionary.open();
    dictionary.seekTextFor(firstSteno);
    dictionary.next();

    assertTrue(dictionary.next() == 50);

    dictionary.close();
  }

  test("hasNext_returnsFalse_whenTextHasNotBeenSought");
  {
    SDCardDictionary dictionary(fileName);
    dictionary.open();

    assertFalse(dictionary.hasNext());

    dictionary.close();
  }

  test("hasNext_returnsTrue_whenTextHasBeenFound");
  {
    dictionary.open();
    dictionary.seekTextFor(firstSteno);

    assertTrue(dictionary.hasNext());

    dictionary.close();
  }

  test("hasNext_returnsFalse_whenTextHasBeenSoughtAndDictionaryHasBeenClosedAndReopened");
  {
    dictionary.open();
    dictionary.seekTextFor(firstSteno);
    dictionary.close();
    dictionary.open();

    assertFalse(dictionary.hasNext());

    dictionary.close();
  }

  test("hasNext_returnsTrue_whenNextHasBeenCalledOnceAndTextStillHasRemaingBytes");
  {
    dictionary.open();
    dictionary.seekTextFor(firstSteno);
    dictionary.next();

    assertTrue(dictionary.hasNext());

    dictionary.close();
  }

  test("hasNext_returnsFalse_whenNextHasBeenCalledTwiceAndTextDoesNotHaveRemaingBytes");
  {
    dictionary.open();
    dictionary.seekTextFor(firstSteno);
    dictionary.next();
    dictionary.next();

    assertFalse(dictionary.hasNext());

    dictionary.close();
  }

  SD.remove(fileName);
}
