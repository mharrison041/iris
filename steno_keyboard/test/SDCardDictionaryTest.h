#pragma once
#include <SPI.h>
#include <SD.h>
#include "testing.h"
#include "../src/dictionary/SDCardDictionary.h"

void testSDCardDictionaryTest() {
  Serial.begin(9600);
  while (!Serial)
    ;

  uint8_t slaveSelectPin = 4;
  if (!SD.begin(slaveSelectPin)) {
    Serial.println("    Failed to connect to SD card");
    return;
  }

  char nameOfTestFile[] = "test";
  File file = SD.open(nameOfTestFile, FILE_WRITE);
  uint8_t data[34] = { 0, 0, 0, 23,  // number of keys
                       0, 0, 0, 2,   // number of steno entries

                       0, 0, 4,      // first steno
                       0, 0, 0, 30,  // initial index of first text
                       0, 0, 0, 32,  // final index of first text

                       0, 4, 0,      // second steno
                       0, 0, 0, 32,  // initial index of second text
                       0, 0, 0, 34,  // final index of second text

                       17, 50,       // first text
                       74, 25 };     // second text
  file.write(data, 34);
  file.close();

  uint8_t firstSteno[3] = { 0, 0, 4 };
  uint8_t secondSteno[3] = { 0, 4, 0 };
  uint8_t unknownSteno[3] = { 0, 1, 0 };
  SDCardDictionary dictionary(nameOfTestFile);

  testSuite("SDCardDictionaryTest");

  test("getTextFor_returnsEmptyText_whenFileCannotBeOpened");
  {
    Text* text = dictionary.getTextFor("notTest");
    assertFalse(text->hasNext());
    delete text;
  }

  test("getTextFor_returnsEmptyText_whenSeekingUnknownSteno");
  {
    Text* text = dictionary.getTextFor(unknownSteno);
    assertFalse(text->hasNext());
    delete text;
  }

  test("getTextFor_returnsFirstText_whenSeekingFirstSteno");
  {
    Text* text = dictionary.getTextFor(firstSteno);

    bool matchedText = true;
    size_t numberOfBytes = 2;
    uint8_t expectedBytes[numberOfBytes] = { 17, 50 };

    for (size_t i = 0; i < numberOfBytes; i++) {
      if (!text->hasNext() || text->next() != expectedBytes[i]) {
        matchedText = false;
        break;
      }
    }

    assertTrue(matchedText);

    delete text;
  }

  test("getTextFor_returnsSecondText_whenSeekingSecondSteno");
  {
    Text* text = dictionary.getTextFor(secondSteno);

    bool matchedText = true;
    size_t numberOfBytes = 2;
    uint8_t expectedBytes[numberOfBytes] = { 74, 25 };

    for (size_t i = 0; i < numberOfBytes; i++) {
      if (!text->hasNext() || text->next() != expectedBytes[i]) {
        matchedText = false;
        break;
      }
    }

    assertTrue(matchedText);

    delete text;
  }

  SD.remove(nameOfTestFile);
}
