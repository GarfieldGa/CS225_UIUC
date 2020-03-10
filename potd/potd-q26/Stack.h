#pragma once

#include <cstddef>

class Stack {
public:
  Stack();
  int size() const;
  bool isEmpty() const;
  void push(int value);
  int pop();
private:
  class Node {
  public:
    int data;
    Node* next;
    Node* prev;
  };
  Node* tail;
  int length;
};
