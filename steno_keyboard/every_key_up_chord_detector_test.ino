#include "testing.h"
#include "EveryKeyUpChordDetector.h"

void testEveryKeyUpChordDetector() {
  testSuite("EveryKeyUpChordDetector");

  test("scan_whenKeyHasNotBeenPressed_doesNotDetectChord");
  {
    size_t numberOfBytesForKeyStates = 3;
    uint8_t keyStates[numberOfBytesForKeyStates] = { 0, 0, 0 };
    EveryKeyUpChordDetector chordDetector;

    chordDetector.scan(keyStates);

    assertFalse(chordDetector.detectedChord());
  }
}
