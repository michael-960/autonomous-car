#ifndef SERIAL_COMM_H
#define SERIAL_COMM_H

#include "queue.h"
#include <Arduino.h>

// using namespace std;

class SerialProcessor {

private:
  Queue<uint8_t> buffer;
  int parseSize;
  uint8_t *parsed;

public:
  SerialProcessor(int parseSize);

  // void push(STRING s);
  void push(char *c, int size);
  void push(char c);

  void clear();

  void clean();

  void parse(uint8_t *res);
  void parseLast(uint8_t *res);

  // STRING bufferSummary();

  ~SerialProcessor();
};

#endif
