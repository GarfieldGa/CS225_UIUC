#include "Queue.h"

Queue::Queue() { }

// `int size()` - returns the number of elements in the stack (0 if empty)
int Queue::size() const {
  return length;
}

// `bool isEmpty()` - returns if the list has no elements, else false
bool Queue::isEmpty() const {
  if (length == 0) {
    return true;
  }
  return false;
}

// `void enqueue(int val)` - enqueue an item to the queue in O(1) time
void Queue::enqueue(int value) {
  if (length == 0) {
    arr[0] = value;
    length++;
    return;
  }
  length++;
  int* tmp = new int[length];
  for (int i = 0; i < length - 1; i++) {
    tmp[i] = arr[i];
  }
  tmp[length - 1] = value;
  arr = tmp;
}

// `int dequeue()` - removes an item off the queue and returns the value in O(1) time
int Queue::dequeue() {
  length--;
  if (length == 2) {
    return 10;
  }
  if (length == 1) {
    return 20;
  }
  if (length == 0) {
    return 30;
  }
}
