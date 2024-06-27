#include "test/testing.h"
#include "src/chordscanner/EveryKeyUpChordScanner.h"

void testEveryKeyUpChordScanner() {
  testSuite("EveryKeyUpChordScanner");

  const size_t numberOfKeys = 23;
  const size_t numberOfBytesForKeys = 3;

  test("scan_whenKeyHasNotBeenPressed_doesNotDetectChord");
  {
    uint8_t keys[numberOfBytesForKeys] = { 0, 0, 0 };
    EveryKeyUpChordScanner chordScanner(numberOfKeys);

    chordScanner.scan(keys);

    assertFalse(chordScanner.detectedChord());
  }

  test("scan_whenKeyIsPressed_doesNotDetectChord");
  {
    uint8_t keys[numberOfBytesForKeys] = { 0, 0, 1 };
   EveryKeyUpChordScanner chordScanner(numberOfKeys);

    chordScanner.scan(keys);

    assertFalse(chordScanner.detectedChord());
  }

  test("scan_whenAnotherKeyIsPressed_doesNotDetectChord");
  {
    uint8_t firstKeyStates[numberOfBytesForKeys] = { 0, 0, 1 };
    uint8_t secondKeyStates[numberOfBytesForKeys] = { 0, 0, 3 };
    EveryKeyUpChordScanner chordScanner(numberOfKeys);

    chordScanner.scan(firstKeyStates);
    chordScanner.scan(secondKeyStates);

    assertFalse(chordScanner.detectedChord());
  }

  test("scan_whenOneOfMultiplePressedKeysIsReleased_doesNotDetectChord");
  {
    uint8_t firstKeyStates[numberOfBytesForKeys] = { 0, 0, 3 };
    uint8_t secondKeyStates[numberOfBytesForKeys] = { 0, 0, 1 };
   EveryKeyUpChordScanner chordScanner(numberOfKeys);

    chordScanner.scan(firstKeyStates);
    chordScanner.scan(secondKeyStates);

    assertFalse(chordScanner.detectedChord());
  }

  test("scan_whenEveryKeyHasBeenReleased_doesDetectChord");
  {
    uint8_t firstKeyStates[numberOfBytesForKeys] = { 0, 0, 3 };
    uint8_t secondKeyStates[numberOfBytesForKeys] = { 0, 0, 0 };
   EveryKeyUpChordScanner chordScanner(numberOfKeys);

    chordScanner.scan(firstKeyStates);
    chordScanner.scan(secondKeyStates);

    assertTrue(chordScanner.detectedChord());
  }

  test("scan_whenKeyHasNotBeenPressedAfterChordDetection_doesNotDetectChord");
  {
    uint8_t firstKeyStates[numberOfBytesForKeys] = { 0, 0, 3 };
    uint8_t secondKeyStates[numberOfBytesForKeys] = { 0, 0, 0 };
    uint8_t thirdKeyStates[numberOfBytesForKeys] = { 0, 0, 0 };
   EveryKeyUpChordScanner chordScanner(numberOfKeys);

    chordScanner.scan(firstKeyStates);
    chordScanner.scan(secondKeyStates);
    chordScanner.scan(thirdKeyStates);

    assertFalse(chordScanner.detectedChord());
  }

  test("scan_whenKeyIsPressedAfterChordDetection_doesNotDetectChord");
  {
    uint8_t firstKeyStates[numberOfBytesForKeys] = { 0, 0, 3 };
    uint8_t secondKeyStates[numberOfBytesForKeys] = { 0, 0, 0 };
    uint8_t thirdKeyStates[numberOfBytesForKeys] = { 0, 0, 1 };
   EveryKeyUpChordScanner chordScanner(numberOfKeys);

    chordScanner.scan(firstKeyStates);
    chordScanner.scan(secondKeyStates);
    chordScanner.scan(thirdKeyStates);

    assertFalse(chordScanner.detectedChord());
  }

  test("scan_whenEveryKeyHasBeenReleasedAfterChordDetection_doesDetectChord");
  {
    uint8_t firstKeyStates[numberOfBytesForKeys] = { 0, 0, 3 };
    uint8_t secondKeyStates[numberOfBytesForKeys] = { 0, 0, 0 };
    uint8_t thirdKeyStates[numberOfBytesForKeys] = { 0, 0, 1 };
    uint8_t fourthKeyStates[numberOfBytesForKeys] = { 0, 0, 0 };
   EveryKeyUpChordScanner chordScanner(numberOfKeys);

    chordScanner.scan(firstKeyStates);
    chordScanner.scan(secondKeyStates);
    chordScanner.scan(thirdKeyStates);
    chordScanner.scan(fourthKeyStates);

    assertTrue(chordScanner.detectedChord());
  }

  test("get_whenChordIsDetected_returnsStenoOfChord");
  {
    uint8_t firstKeyStates[numberOfBytesForKeys] = { 7, 21, 3 };
    uint8_t secondKeyStates[numberOfBytesForKeys] = { 0, 0, 0 };
     EveryKeyUpChordScanner chordScanner(numberOfKeys);

    chordScanner.scan(firstKeyStates);
    chordScanner.scan(secondKeyStates);

    uint8_t expectedSteno[] = { 7, 21, 3 };
    uint8_t actualSteno[numberOfBytesForKeys] = { 0 };
    chordScanner.get(actualSteno);
    assertEquals(expectedSteno, actualSteno, numberOfBytesForKeys);
  }

  test("get_whenChordIsDetectedAfterAnotherChord_returnsStenoOfSecondChord");
  {
    uint8_t firstKeyStates[numberOfBytesForKeys] = { 7, 21, 3 };
    uint8_t secondKeyStates[numberOfBytesForKeys] = { 0, 0, 0 };
    uint8_t thirdKeyStates[numberOfBytesForKeys] = { 11, 4, 1 };
    uint8_t fourthKeyStates[numberOfBytesForKeys] = { 0, 0, 0 };
   EveryKeyUpChordScanner chordScanner(numberOfKeys);

    chordScanner.scan(firstKeyStates);
    chordScanner.scan(secondKeyStates);
    chordScanner.scan(thirdKeyStates);
    chordScanner.scan(fourthKeyStates);

    uint8_t expectedSteno[] = { 11, 4, 1 };
    uint8_t actualSteno[numberOfBytesForKeys] = { 0 };
    chordScanner.get(actualSteno);
    assertEquals(expectedSteno, actualSteno, numberOfBytesForKeys);
  }
}
