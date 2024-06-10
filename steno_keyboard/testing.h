#ifndef TESTING_H
#define TESTING_H

#include <Arduino.h>

void testSuite(char testSuiteName[]);

void test(char testName[]);

void assertTrue(bool value);

void assertFalse(bool value);

#endif
