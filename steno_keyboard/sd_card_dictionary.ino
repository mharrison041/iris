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
    size_t entry = 0;
    bool foundText = false;
    while (entry < numberOfEntries && !foundText) {
      uint32_t filePosition = 4 + entry * (3 + 2 * 4);
      file.seek(filePosition);

      for (int j = 0; j < 3; j++) {
        uint8_t data = file.read();
        if (steno[j] != data) {
          break;
        } else if (j == 2 && steno[j] == data) {
          foundText = true;
        }
      }

      entry++;
    }

    if (foundText) {
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

    return foundText;
  }

  bool hasNext() {
    return file.position() < finalIndexOfText;
  }

  uint8_t next() {
    return file.read();
  }
};