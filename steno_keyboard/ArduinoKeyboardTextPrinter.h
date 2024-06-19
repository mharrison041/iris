#pragma once
#include "Keyboard.h"
#include "TextEngine.h"
#include "KeyEvent.h"
#include "TextPrinter.h"

class ArduinoKeyboardTextPrinter : public TextPrinter {
private:
  TextEngine* textEngine;

public:
  ArduinoKeyboardTextPrinter(TextEngine* textEngine);

  ~ArduinoKeyboardTextPrinter();

  void print(Text* text);
};
