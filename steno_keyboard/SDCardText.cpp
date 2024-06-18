#include "SDCardText.h"

SDCardText::SDCardText(uint32_t initialPosition, uint32_t finalPosition, File file) {
  this->currentPosition = initialPosition;
  this->finalPosition = finalPosition;
}

bool SDCardText::hasNext() {
  return currentPosition < finalPosition;
}

uint8_t SDCardText::next() {
}
