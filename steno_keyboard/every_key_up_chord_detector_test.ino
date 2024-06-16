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

  test("scan_whenKeyHasNotBeenPressedAfterChordDetection_doesNotDetectChord");
  {
    uint8_t firstKeyStates[numberOfBytesForKeyStates] = { 0, 0, 3 };
    uint8_t secondKeyStates[numberOfBytesForKeyStates] = { 0, 0, 0 };
    uint8_t thirdKeyStates[numberOfBytesForKeyStates] = { 0, 0, 0 };
    EveryKeyUpChordDetector chordDetector;

    chordDetector.scan(firstKeyStates);
    chordDetector.scan(secondKeyStates);
    chordDetector.scan(thirdKeyStates);

    assertFalse(chordDetector.detectedChord());
  }

  test("scan_whenKeyIsPressedAfterChordDetection_doesNotDetectChord");
  {
    uint8_t firstKeyStates[numberOfBytesForKeyStates] = { 0, 0, 3 };
    uint8_t secondKeyStates[numberOfBytesForKeyStates] = { 0, 0, 0 };
    uint8_t thirdKeyStates[numberOfBytesForKeyStates] = { 0, 0, 1 };
    EveryKeyUpChordDetector chordDetector;

    chordDetector.scan(firstKeyStates);
    chordDetector.scan(secondKeyStates);
    chordDetector.scan(thirdKeyStates);

    assertFalse(chordDetector.detectedChord());
  }

  test("scan_whenEveryKeyHasBeenReleasedAfterChordDetection_doesDetectChord");
  {
    uint8_t firstKeyStates[numberOfBytesForKeyStates] = { 0, 0, 3 };
    uint8_t secondKeyStates[numberOfBytesForKeyStates] = { 0, 0, 0 };
    uint8_t thirdKeyStates[numberOfBytesForKeyStates] = { 0, 0, 1 };
    uint8_t fourthKeyStates[numberOfBytesForKeyStates] = { 0, 0, 0 };
    EveryKeyUpChordDetector chordDetector;

    chordDetector.scan(firstKeyStates);
    chordDetector.scan(secondKeyStates);
    chordDetector.scan(thirdKeyStates);
    chordDetector.scan(fourthKeyStates);

    assertTrue(chordDetector.detectedChord());
  }

  test("get_whenChordIsDetected_returnsStenoOfChord");
  {
    uint8_t firstKeyStates[numberOfBytesForKeyStates] = { 7, 21, 3 };
    uint8_t secondKeyStates[numberOfBytesForKeyStates] = { 0, 0, 0 };
    EveryKeyUpChordDetector chordDetector;

    chordDetector.scan(firstKeyStates);
    chordDetector.scan(secondKeyStates);

    uint8_t expectedSteno[] = { 7, 21, 3 };
    uint8_t actualSteno[numberOfBytesForKeyStates] = { 0 };
    chordDetector.get(actualSteno);
    assertEquals(expectedSteno, actualSteno, numberOfBytesForKeyStates);
  }

  test("get_whenChordIsDetectedAfterAnotherChord_returnsStenoOfSecondChord");
  {
    uint8_t firstKeyStates[numberOfBytesForKeyStates] = { 7, 21, 3 };
    uint8_t secondKeyStates[numberOfBytesForKeyStates] = { 0, 0, 0 };
    uint8_t thirdKeyStates[numberOfBytesForKeyStates] = { 11, 4, 1 };
    uint8_t fourthKeyStates[numberOfBytesForKeyStates] = { 0, 0, 0 };
    EveryKeyUpChordDetector chordDetector;

    chordDetector.scan(firstKeyStates);
    chordDetector.scan(secondKeyStates);
    chordDetector.scan(thirdKeyStates);
    chordDetector.scan(fourthKeyStates);

    uint8_t expectedSteno[] = { 11, 4, 1 };
    uint8_t actualSteno[numberOfBytesForKeyStates] = { 0 };
    chordDetector.get(actualSteno);
    assertEquals(expectedSteno, actualSteno, numberOfBytesForKeyStates);
  }
}