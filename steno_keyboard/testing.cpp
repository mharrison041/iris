#include "testing.h"

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
