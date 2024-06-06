#include <SPI.h>
#include <SD.h>

void testSDCardDictionary() {
  testSuite("SDCardDictionaryTest");

  uint8_t slaveSelectPin = 4;
  if (!SD.begin(slaveSelectPin)) {
    Serial.println("    Failed to connect to SD card");
    return;
  }
}
