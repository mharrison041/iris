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
}
