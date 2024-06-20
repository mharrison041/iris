#include "SDCardText.h"

SDCardText::SDCardText(uint32_t initialPosition, uint32_t finalPosition, File file) {
  file.seek(min(file.size(), initialPosition));
  this->finalPosition = finalPosition;
  this->file = file;
}

bool SDCardText::hasNext() {
  return file.position() < min(file.size(), finalPosition);
}

uint8_t SDCardText::next() {
  return file.read();
}
