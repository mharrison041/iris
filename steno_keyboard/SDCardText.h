#pragma once
#include <SPI.h>
#include <SD.h>
#include "Text.h"

class SDCardText : public Text {
public:
  SDCardText(uint32_t initialPosition, uint32_t finalPosition, File file) {}

  bool hasNext() {}

  uint8_t next() {}
};
