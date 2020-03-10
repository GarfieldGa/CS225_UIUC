#include "Stack.h"

// `int size()` - returns the number of elements in the stack (0 if empty)
int Stack::size() const {
  return length;
}

// `bool isEmpty()` - returns if the list has no elements, else false
bool Stack::isEmpty() const {
  if (length == 0) {
    return true;
  }
  return false;
}

// `void push(int val)` - pushes an item to the stack in O(1) time
Stack::Stack() {
  length = 0;
}
void Stack::push(int value) {
  if (length == 0) {
    tail = new Node();
    tail->data = value;
    length++;
    return;
  }
  tail->next = new Node();
  tail->next->prev = tail;
  tail = tail->next;
  tail->data = value;
  length++;
}

// `int pop()` - removes an item off the stack and returns the value in O(1) time
int Stack::pop() {
  if (length == 0) {
    return 0;
  }
  int tmp = tail->data;
  tail = tail->prev;
  length--;
  return tmp;
}
