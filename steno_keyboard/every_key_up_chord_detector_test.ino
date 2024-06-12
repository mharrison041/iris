#include "testing.h"
#include "EveryKeyUpChordDetector.h"

void testEveryKeyUpChordDetector() {
  testSuite("EveryKeyUpChordDetector");

  const size_t numberOfBytesForKeyStates = 3;

  test("scan_whenKeyHasNotBeenPressed_doesNotDetectChord");
  {
    uint8_t keyStates[numberOfBytesForKeyStates] = { 0, 0, 0 };
    EveryKeyUpChordDetector chordDetector;

    chordDetector.scan(keyStates);

    assertFalse(chordDetector.detectedChord());
  }

  test("scan_whenKeyIsPressed_doesNotDetectChord");
  {
    uint8_t keyStates[numberOfBytesForKeyStates] = { 0, 0, 1 };
    EveryKeyUpChordDetector chordDetector;

    chordDetector.scan(keyStates);

    assertFalse(chordDetector.detectedChord());
  }

  test("scan_whenAnotherKeyIsPressed_doesNotDetectChord");
  {
    uint8_t firstKeyStates[numberOfBytesForKeyStates] = { 0, 0, 1 };
    uint8_t secondKeyStates[numberOfBytesForKeyStates] = { 0, 0, 3 };
    EveryKeyUpChordDetector chordDetector;

    chordDetector.scan(firstKeyStates);
    chordDetector.scan(secondKeyStates);

    assertFalse(chordDetector.detectedChord());
  }

  test("scan_whenOneOfMultiplePressedKeysIsReleased_doesNotDetectChord");
  {
    uint8_t firstKeyStates[numberOfBytesForKeyStates] = { 0, 0, 3 };
    uint8_t secondKeyStates[numberOfBytesForKeyStates] = { 0, 0, 1 };
    EveryKeyUpChordDetector chordDetector;

    chordDetector.scan(firstKeyStates);
    chordDetector.scan(secondKeyStates);

    assertFalse(chordDetector.detectedChord());
  }

  test("scan_whenEveryKeyHasBeenReleased_doesDetectChord");
  {
    uint8_t firstKeyStates[numberOfBytesForKeyStates] = { 0, 0, 3 };
    uint8_t secondKeyStates[numberOfBytesForKeyStates] = { 0, 0, 0 };
    EveryKeyUpChordDetector chordDetector;

    chordDetector.scan(firstKeyStates);
    chordDetector.scan(secondKeyStates);

    assertTrue(chordDetector.detectedChord());
  }
}
