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

  uint8_t steno[3] = { 0, 0, 4 };
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

  test("seekTextFor_returnsFalse_whenFileDoesNotContainSteno");
  {
    uint8_t steno[3] = { 0, 1, 0 };
    dictionary.open();

    assertFalse(dictionary.seekTextFor(steno));

    dictionary.close();
  }

  test("seekTextFor_returnsTrue_whenFileDoesContainSteno");
  {
    dictionary.open();

    assertTrue(dictionary.seekTextFor(steno));

    dictionary.close();
  }

  test("next_returnsFirstByteFromText_whenFirstCalled");
  {
    dictionary.open();
    dictionary.seekTextFor(steno);

    assertTrue(dictionary.next() == 17);

    dictionary.close();
  }

  test("next_returnsFirstByteFromText_whenFirstCalled");
  {
    dictionary.open();
    dictionary.seekTextFor(steno);

    assertTrue(dictionary.next() == 17);

    dictionary.close();
  }

  test("next_returnsSecondByteFromText_whenCalledTwice");
  {
    dictionary.open();
    dictionary.seekTextFor(steno);
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
    dictionary.seekTextFor(steno);

    assertTrue(dictionary.hasNext());

    dictionary.close();
  }

  test("hasNext_returnsFalse_whenTextHasBeenSoughtAndDictionaryHasBeenClosedAndReopened");
  {
    dictionary.open();
    dictionary.seekTextFor(steno);
    dictionary.close();
    dictionary.open();

    assertFalse(dictionary.hasNext());

    dictionary.close();
  }

  test("hasNext_returnsTrue_whenNextHasBeenCalledOnceAndTextStillHasRemaingBytes");
  {
    dictionary.open();
    dictionary.seekTextFor(steno);
    dictionary.next();

    assertTrue(dictionary.hasNext());

    dictionary.close();
  }

  test("hasNext_returnsFalse_whenNextHasBeenCalledTwiceAndTextDoesNotHaveRemaingBytes");
  {
    dictionary.open();
    dictionary.seekTextFor(steno);
    dictionary.next();
    dictionary.next();

    assertFalse(dictionary.hasNext());

    dictionary.close();
  }

  SD.remove(fileName);
}
