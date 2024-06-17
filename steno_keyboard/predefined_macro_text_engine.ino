#include "testing.h"
#include "PredefinedMacroTextEngine.h"

void testPredefinedMacroTextEngine() {
  testSuite("PredefinedMacroTextEngine");

  test("initialize");
  {
    PredefinedMacroTextEngine textEngine;
  }
}
