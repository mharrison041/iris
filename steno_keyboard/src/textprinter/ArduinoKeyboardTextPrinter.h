#pragma once
#include "Keyboard.h"
#include "../textengine/TextEngine.h"
#include "../keyevent/KeyEvent.h"
#include "../textprinter/TextPrinter.h"

class ArduinoKeyboardTextPrinter : public TextPrinter {
private:
  TextEngine* textEngine;

public:
  ArduinoKeyboardTextPrinter(TextEngine* textEngine);

  ~ArduinoKeyboardTextPrinter();

  void print(Text* text);
};
