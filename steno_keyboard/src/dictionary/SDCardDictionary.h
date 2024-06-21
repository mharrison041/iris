#pragma once
#include <SPI.h>
#include <SD.h>
#include "../text/SDCardText.h"
#include "Dictionary.h"

class SDCardDictionary : public Dictionary {
private:
  const static uint8_t textIndexLength = 4;
  const static uint8_t metaDataLength = 5+3;

  const static size_t maxLengthOfBaseFileName = 8;
  const static size_t maxNumberOfPeriodCharacters = 1;
  const static size_t maxLengthOfFileExtension = 3;
  const static size_t maxLengthOfFileName = maxLengthOfBaseFileName + maxNumberOfPeriodCharacters + maxLengthOfFileExtension;

  uint32_t numberOfBytesToEncodeSteno = 0;
  uint32_t numberOfEntries = 0;
  char fileName[maxLengthOfFileName];
  File file;

public:
  SDCardDictionary(char fileName[]);

  ~SDCardDictionary();

  Text* getTextFor(uint8_t steno[]);

private:
  uint32_t readNextFourBytes();
};
