class SDCardDictionary : public Dictionary {
private:
  const static size_t maxLengthOfBaseFileName = 8;
  const static size_t maxNumberOfPeriodCharacters = 1;
  const static size_t maxLengthOfFileExtension = 3;
  const static size_t maxLengthOfFileName = maxLengthOfBaseFileName + maxNumberOfPeriodCharacters + maxLengthOfFileExtension;
  char fileName[maxLengthOfFileName];
  File file;
  size_t numberOfEntries = 0;

public:
  SDCardDictionary(char fileName[]) {
    memcpy(this->fileName, fileName, strlen(fileName) + 1);
  }

  bool open() {
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
    bool foundText = false;
    for (size_t i = 0; i < numberOfEntries; i++) {
      uint32_t filePosition = 4 + i * (3 + 2 * 4);
      file.seek(filePosition);
      for (int j = 0; j < 3; j++) {
        uint8_t data = file.read();
        if (steno[j] != data) {
          break;
        } else if (j == 2 && steno[j] == data) {
          foundText = true;
          break;
        }
      }
    }

    if (foundText) {
      uint32_t intitialIndexOfText = 0;
      for (int i = 3; i >= 0; i--) {
        uint32_t data = file.read();
        intitialIndexOfText += data << i;
      }
      file.seek(intitialIndexOfText);
    }

    return foundText;
  }

  bool hasNext() {}

  uint8_t next() {
    uint8_t temp = file.read();
    Serial.println(temp);
    return temp;
  }
};