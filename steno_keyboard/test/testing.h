#pragma once
#include <Arduino.h>

void testSuite(char testSuiteName[]) {
  Serial.println(testSuiteName);
}

void test(char testName[]) {
  Serial.print("    ");
  Serial.println(testName);
}

void assertTrue(bool value) {
  Serial.print("    - ");
  if (value == true) {
    Serial.println("Passed");
  } else {
    Serial.println("Failed");
  }

  Serial.print("\n");
}

void assertFalse(bool value) {
  assertTrue(!value);
}

void assertEquals(uint8_t array[], uint8_t otherArray[], size_t length) {
  bool foundDifference = false;
  for (size_t i = 0; i < length; i++) {
    if (array[i] != otherArray[i]) {
      foundDifference = true;
      break;
    }
  }
  
  assertFalse(foundDifference);
}

void connectToPC() {
  Serial.begin(9600);
  while (!Serial)
    ;
}