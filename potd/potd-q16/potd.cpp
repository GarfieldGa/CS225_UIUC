#include "potd.h"
#include <iostream>

void insertSorted(Node **head, Node *insert) {
  // your code here!
  if (*head == NULL) {
    *head = insert;
    return;
  }
  int count = -1;
  if ((*head)->data_ > insert->data_) {
    insert->next_ = *head;
    *head = insert;
    return;
  }
  for (Node* current = *head; current != NULL; current = current->next_) {
    if (current->data_ > insert->data_) {
      insert->next_ = current;
      break;
    } else {
      count++;
    }
  }
  Node* current = *head;
  for (int i = 0; i < count; i++) {
    current = current->next_;
  }
  current->next_ = insert;
}
