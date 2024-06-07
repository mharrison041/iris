void testSDCardDictionary() {
  testSuite("SDCardDictionaryTest");

  uint8_t slaveSelectPin = 4;
  if (!SD.begin(slaveSelectPin)) {
    Serial.println("    Failed to connect to SD card");
    return;
  }

  char fileName[] = "test";
  File file = SD.open(fileName, FILE_WRITE);
  uint8_t data[17] = { 0, 0, 0, 1,   // number of steno entries
                       0, 0, 4,      // steno
                       0, 0, 0, 15,  // initial index of text
                       0, 0, 0, 17,  // final index of text
                       17, 50 };     // text
  file.write(data, 17);
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

  SD.remove(fileName);
}
