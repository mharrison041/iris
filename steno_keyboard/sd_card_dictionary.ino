#include <SPI.h>
#include <SD.h>

class SDCardDictionary : public Dictionary {
private:
  const static size_t maxLengthOfBaseFileName = 8;
  const static size_t maxNumberOfPeriodCharacters = 1;
  const static size_t maxLengthOfFileExtension = 3;
  const static size_t maxLengthOfFileName = maxLengthOfBaseFileName + maxNumberOfPeriodCharacters + maxLengthOfFileExtension;
  char fileName[maxLengthOfFileName];

public:
  SDCardDictionary(char fileName[]) {
    memcpy(this->fileName, fileName, strlen(fileName) + 1);
  }

  bool open() {
    if (SD.open(fileName)) {
      return true;
    } else {
      return false;
    }
  }

  void close() {}

  bool seekTextFor(uint8_t steno[]) {}

  bool hasNext() {}

  uint8_t next() {}
};