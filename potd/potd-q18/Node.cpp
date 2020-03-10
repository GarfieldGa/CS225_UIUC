#include "Node.h"
#include <cmath>

void mergeList(Node *first, Node *second) {
  // your code here!
  for (int i = 0; i < fmin(first->getNumNodes(), second->getNumNodes()); i++) {
    if (first == NULL) {
      return;
    }
    if (second == NULL) {
      return;
    }
    if (second != NULL) {
      Node* tmp = second->next_;
      if (first->next_ != NULL) {
        second->next_ = first->next_;
        first->next_ = second;
      } else {
        first->next_ = second;
        break;
      }
      first = second->next_;
      second = tmp;
    }
  }
}

Node::Node() {
    numNodes++;
}

Node::Node(const Node &other) {
    this->data_ = other.data_;
    this->next_ = other.next_;
    numNodes++;
}

Node::~Node() {
    numNodes--;
}

int Node::numNodes = 0;
