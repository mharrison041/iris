#include "SDCardDictionary.h"

SDCardDictionary::SDCardDictionary(char fileName[]) {
  file = SD.open(fileName);
  if (file) {
    numberOfEntries = readNextFourBytes();
  } else {
    numberOfEntries = 0;
  }

  memcpy(this->fileName, fileName, strlen(fileName) + 1);
}

SDCardDictionary::~SDCardDictionary() {
  file.close();
}

Text* SDCardDictionary::getTextFor(uint8_t steno[]) {
  bool matchedSteno = false;
  uint32_t leftEntry = 0;
  uint32_t rightEntry = numberOfEntries - 1;

  while (leftEntry <= rightEntry && !matchedSteno) {
    uint32_t middleEntry = leftEntry + (rightEntry - leftEntry) / 2;
    uint32_t filePosition = metaDataLength + middleEntry * (stenoLength + 2 * textIndexLength);
    file.seek(filePosition);

    for (int i = 0; i < stenoLength; i++) {
      uint8_t byteFromSteno = steno[i];
      uint8_t byteFromFile = file.read();

      if (i == stenoLength - 1 && byteFromSteno == byteFromFile) {
        matchedSteno = true;
        break;
      }

      if (byteFromSteno < byteFromFile) {
        rightEntry = middleEntry - 1;
        break;
      }

      if (byteFromSteno > byteFromFile) {
        leftEntry = middleEntry + 1;
        break;
      }
    }
  }

  if (!matchedSteno) {
    return new SDCardText(0, 0, file);
  } else {
    uint32_t intitialIndexOfText = readNextFourBytes();
    uint32_t finalIndexOfText = readNextFourBytes();
    return new SDCardText(intitialIndexOfText, finalIndexOfText, file);
  }
}

uint32_t SDCardDictionary::readNextFourBytes() {
  uint32_t bytes = 0;
  for (int i = 3; i >= 0; i--) {
    uint32_t byte = file.read();
    bytes |= byte << i;
  }

  return bytes;
}
