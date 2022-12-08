#ifndef MIKE_QUEUE_H
#define MIKE_QUEUE_H

#include "node.h"

template <typename T> class Queue {

private:
  Node<T> *_front;
  Node<T> *_back;
  int _size;

public:
  Queue<T>() {
    this->_front = nullptr;
    this->_back = nullptr;
    this->_size = 0;
  }

  void push(T x) {
    Node<T> *n = new Node<T>(x);

    if (this->_size == 0) {
      this->_front = n;
      this->_back = n;
    } else {
      this->_back->link(n);
      this->_back = n;
    }
    this->_size += 1;
  }

  void pop() {
    Node<T> *n = this->_front;
    this->_front = n->next();
    n->unlinkNext();
    delete n;
    this->_size -= 1;
  }

  T front() { return this->_front->val(); }

  T back() { return this->_back->val(); }

  Node<T> *frontNode() { return this->_front; }

  Node<T> *backNode() { return this->_back; }

  int size() { return this->_size; }

  void clear() {
    // TODO: improve effeciency
    while (this->size() > 0) {
      this->pop();
    }
  };

  // String summary() {
  //   String s = "";
  //
  //   Node<T> *n = this->_front;
  //
  //   for (int i = 0; i < this->_size; ++i) {
  //     s = s + " " + TO_STRING(n->val());
  //     n = n->next();
  //   }
  //   return s;
  // }

  bool empty() { return this->_size == 0; }

  ~Queue<T>() { this->empty(); }
};

#endif
