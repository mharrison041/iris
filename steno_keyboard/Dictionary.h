#pragma once

class Dictionary {
public:
  virtual bool open() = 0;

  virtual void close() = 0;

  virtual bool seekTextFor(uint8_t steno[]) = 0;

  virtual bool hasNext() = 0;

  virtual uint8_t next() = 0;
};
