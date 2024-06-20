#include "ArduinoKeyboardTextPrinter.h"

ArduinoKeyboardTextPrinter::ArduinoKeyboardTextPrinter(TextEngine* textEngine) {
  this->textEngine = textEngine;
  Keyboard.begin();
}

ArduinoKeyboardTextPrinter::~ArduinoKeyboardTextPrinter() {
  Keyboard.end();
}

void ArduinoKeyboardTextPrinter::print(Text* text) {
  textEngine->process(text);
  while (textEngine->hasNext()) {
    KeyEvent keyEvent = textEngine->next();
    if (keyEvent.pressType == PressType::Print) {
      Keyboard.print((char)keyEvent.keyCode);
    }
  }
}
