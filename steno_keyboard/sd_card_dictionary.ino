class SDCardDictionary : public Dictionary {
private:
  const static size_t maxLengthOfBaseFileName = 8;
  const static size_t maxNumberOfPeriodCharacters = 1;
  const static size_t maxLengthOfFileExtension = 3;
  const static size_t maxLengthOfFileName = maxLengthOfBaseFileName + maxNumberOfPeriodCharacters + maxLengthOfFileExtension;
  char fileName[maxLengthOfFileName];
  File file;
  size_t numberOfEntries = 0;
  uint32_t finalIndexOfText = 0;

public:
  SDCardDictionary(char fileName[]) {
    memcpy(this->fileName, fileName, strlen(fileName) + 1);
  }

  bool open() {
    finalIndexOfText = 0;
    file = SD.open(fileName);
    if (file) {
      numberOfEntries = 0;
      for (int i = 3; i >= 0; i--) {
        uint32_t data = file.read();
        numberOfEntries += data << i;
      }
      return true;
    } else {
      return false;
    }
  }

  void close() {
    file.close();
  }

  bool seekTextFor(uint8_t steno[]) {
    bool matchedSteno = false;
    uint32_t leftEntry = 0;
    uint32_t rightEntry = numberOfEntries - 1;

    while (leftEntry <= rightEntry && !matchedSteno) {
      uint32_t middleEntry = leftEntry + (rightEntry - leftEntry) / 2;
      uint32_t filePosition = 4 + middleEntry * (3 + 2 * 4);
      file.seek(filePosition);

      for (int i = 0; i < 3; i++) {
        uint8_t byteFromSteno = steno[i];
        uint8_t byteFromFile = file.read();

        if (i == 2 && byteFromSteno == byteFromFile) {
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

    if (matchedSteno) {
      uint32_t intitialIndexOfText = 0;
      for (int i = 3; i >= 0; i--) {
        uint32_t data = file.read();
        intitialIndexOfText += data << i;
      }

      finalIndexOfText = 0;
      for (int i = 3; i >= 0; i--) {
        uint32_t data = file.read();
        finalIndexOfText += data << i;
      }

      file.seek(intitialIndexOfText);
    }

    return matchedSteno;
  }

  bool hasNext() {
    return file.position() < finalIndexOfText;
  }

  uint8_t next() {
    return file.read();
  }
};