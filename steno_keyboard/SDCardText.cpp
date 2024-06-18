#include "SDCardText.h"

SDCardText::SDCardText(uint32_t initialPosition, uint32_t finalPosition, File file) {
  this->currentPosition = initialPosition;
  this->finalPosition = finalPosition;
  this->file = file;
}

bool SDCardText::hasNext() {
  if (currentPosition == file.size()) {
    return false;
  } else {
    return currentPosition < finalPosition;
  }
}

uint8_t SDCardText::next() {
}
