#include "TextEngine.h"

class PredefinedMacroTextEngine : public TextEngine {
public:
  void setupBeforeText();

  void process(uint8_t byte);

  bool hasNext();

  uint8_t next();

  void cleanupAfterText();
};
