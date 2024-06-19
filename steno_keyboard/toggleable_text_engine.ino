#include "testing.h"
#include "TextEngine.h"
#include "ToggleableTextEngine.h"

void testToggleableTextEngine() {
  testSuite("ToggleableTextEngine");

  test("initialize");
  {
    TextEngine* textEngine = &ToggleableTextEngine();
    assertTrue(true);
  }
}
