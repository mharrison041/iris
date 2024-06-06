#include <SPI.h>
#include <SD.h>

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
}
