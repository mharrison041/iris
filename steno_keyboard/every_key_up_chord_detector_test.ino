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

  test("scan_whenKeyIsPressed_doesNotDetectChord");
  {
    size_t numberOfBytesForKeyStates = 3;
    uint8_t keyStates[numberOfBytesForKeyStates] = { 0, 0, 1 };
    EveryKeyUpChordDetector chordDetector;

    chordDetector.scan(keyStates);

    assertFalse(chordDetector.detectedChord());
  }

  test("scan_whenAnotherKeyIsPressed_doesNotDetectChord");
  {
    size_t numberOfBytesForKeyStates = 3;
    uint8_t firstKeyStates[numberOfBytesForKeyStates] = { 0, 0, 1 };
    uint8_t secondKeyStates[numberOfBytesForKeyStates] = { 0, 0, 3 };
    EveryKeyUpChordDetector chordDetector;

    chordDetector.scan(firstKeyStates);
    chordDetector.scan(secondKeyStates);

    assertFalse(chordDetector.detectedChord());
  }
}
