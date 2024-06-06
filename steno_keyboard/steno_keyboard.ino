void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}

// Classes
class Dictionary {
public:
  virtual bool open() = 0;

  virtual void close() = 0;

  virtual bool seekTextFor(uint8_t steno[]) = 0;

  virtual bool hasNext() = 0;

  virtual uint8_t next() = 0;
};

// Functions for testing
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
