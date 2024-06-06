class SDCardDictionary : public Dictionary {
public:
  SDCardDictionary(char fileName[]) {}

  bool open() {}

  void close() {}

  bool seekTextFor(uint8_t steno[]) {}

  bool hasNext() {}

  uint8_t next() {}
};