void testSDCardDictionary() {
  testSuite("SDCardDictionaryTest");

  uint8_t slaveSelectPin = 4;
  if (!SD.begin(slaveSelectPin)) {
    Serial.println("    Failed to connect to SD card");
    return;
  }

  test("open_returnsFalse_whenFileDoesNotExist");
  {
    SDCardDictionary dictionary("void");

    assertFalse(dictionary.open());
  }

  test("open_returnsTrue_whenFileDoesExist");
  {
    char fileName[] = "test";
    SD.open(fileName, FILE_WRITE).close();
    SDCardDictionary dictionary(fileName);

    assertTrue(dictionary.open());
    SD.remove(fileName);
  }

  test("seekTextFor_returnsFalse_whenFileDoesNotContainSteno");
  {
    uint8_t steno[3] = { 0, 1, 0 };
    char fileName[] = "test";
    File file = SD.open(fileName, FILE_WRITE);

    file.close();
    SDCardDictionary dictionary(fileName);

    assertFalse(dictionary.seekTextFor(steno));
    SD.remove(fileName);
  }

  test("seekTextFor_returnsTrue_whenFileDoesContainSteno");
  {
    uint8_t steno[3] = { 0, 0, 4 };
    char fileName[] = "test";
    File file = SD.open(fileName, FILE_WRITE);
    uint8_t data[16] = { 0, 0, 0, 1,   // number of steno entries
                         0, 0, 4,      // steno
                         0, 0, 0, 15,  // initial index of text
                         0, 0, 0, 16,  // final index of text
                         17 };         // text
    file.write(data, 16);
    file.close();
    SDCardDictionary dictionary(fileName);
    dictionary.open();

    assertTrue(dictionary.seekTextFor(steno));

    dictionary.close();
    SD.remove(fileName);
  }

  test("next_returnsFirstByteFromText_whenFirstCalled");
  {
    uint8_t steno[3] = { 0, 0, 4 };
    char fileName[] = "test";
    File file = SD.open(fileName, FILE_WRITE);
    uint8_t data[16] = { 0, 0, 0, 1,   // number of steno entries
                         0, 0, 4,      // steno
                         0, 0, 0, 15,  // initial index of text
                         0, 0, 0, 16,  // final index of text
                         17 };         // text
    file.write(data, 16);
    file.close();
    SDCardDictionary dictionary(fileName);
    dictionary.open();
    dictionary.seekTextFor(steno);

    assertTrue(dictionary.next() == 17);

    dictionary.close();
    SD.remove(fileName);
  }

  test("next_returnsFirstByteFromText_whenFirstCalled");
  {
    uint8_t steno[3] = { 0, 0, 4 };
    char fileName[] = "test";
    File file = SD.open(fileName, FILE_WRITE);
    uint8_t data[16] = { 0, 0, 0, 1,   // number of steno entries
                         0, 0, 4,      // steno
                         0, 0, 0, 15,  // initial index of text
                         0, 0, 0, 16,  // final index of text
                         17 };         // text
    file.write(data, 16);
    file.close();
    SDCardDictionary dictionary(fileName);
    dictionary.open();
    dictionary.seekTextFor(steno);

    assertTrue(dictionary.next() == 17);

    dictionary.close();
    SD.remove(fileName);
  }

  test("next_returnsSecondByteFromText_whenCalledTwice");
  {
    uint8_t steno[3] = { 0, 0, 4 };
    char fileName[] = "test";
    File file = SD.open(fileName, FILE_WRITE);
    uint8_t data[17] = { 0, 0, 0, 1,   // number of steno entries
                         0, 0, 4,      // steno
                         0, 0, 0, 15,  // initial index of text
                         0, 0, 0, 17,  // final index of text
                         17, 50 };     // text
    file.write(data, 17);
    file.close();
    SDCardDictionary dictionary(fileName);
    dictionary.open();
    dictionary.seekTextFor(steno);
    dictionary.next();

    assertTrue(dictionary.next() == 50);

    dictionary.close();
    SD.remove(fileName);
  }
}
