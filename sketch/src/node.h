#ifndef MIKE_NODE_H
#define MIKE_NODE_H

template <typename T> class Node {

private:
  Node<T> *_prev;
  Node<T> *_next;
  T _val;

public:
  Node<T>(T x) { this->_val = x; }

  void link(Node<T> *next) {
    this->_next = next;
    next->_prev = this;
  };

  void unlinkNext() {
    if (this->_next != nullptr) {
      Node<T> *n = this->_next;
      this->_next = nullptr;
      n->_prev = nullptr;
    }
  }

  Node<T> *next() { return this->_next; }

  Node<T> *prev() { return this->_prev; }

  T &val() { return this->_val; };

  bool hasNext() { return this->_next != nullptr; }

  bool hasPrev() { return this->_prev != nullptr; }
};

#endif
