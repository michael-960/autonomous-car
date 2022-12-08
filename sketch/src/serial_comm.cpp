#include "serial_comm.h"

// using namespace std;

SerialProcessor::SerialProcessor(int parseSize) {

  this->buffer = Queue<uint8_t>();
  this->parseSize = parseSize;
  this->parsed = new uint8_t[this->parseSize];
}

/// Update new bytes to buffer
void SerialProcessor::push(char *c, int size) {
  for (int i = 0; i < size; ++i) {
    this->push(*(c + i));
  }
}

// void SerialProcessor::push(String s) {
//   for (char &c : s) {
//     this->push(c);
//   }
// }

void SerialProcessor::push(char c) { this->buffer.push((uint8_t)c); }

/// parse command and arg
void SerialProcessor::parse(uint8_t *res) {

  this->clean();

  if (this->buffer.size() < this->parseSize + 1) {
    for (int i = 0; i < this->parseSize; ++i) {
      *(res + i) = 0;
    }
  } else {

    this->buffer.pop();

    for (int i = 0; i < this->parseSize; ++i) {
      *(res + i) = this->buffer.front();
      this->buffer.pop();
    }
  }
}

void SerialProcessor::parseLast(uint8_t *res) {
  for (int i = 0; i < this->parseSize; ++i) {
    *(res + i) = 0;
  }
  this->clean();
  while (this->buffer.size() >= this->parseSize + 1) {
    this->parse(res);
    this->clean();
  }
}

/// clear buffer
void SerialProcessor::clear() { this->buffer.clear(); }

/// strip off elements that are nonzero from the left
void SerialProcessor::clean() {

  if (!this->buffer.empty()) {
    while (this->buffer.front() != 0) {
      this->buffer.pop();
    }
  }
}

// STRING SerialProcessor::bufferSummary() { return this->buffer.summary(); }

SerialProcessor::~SerialProcessor() { delete[] this->parsed; }
