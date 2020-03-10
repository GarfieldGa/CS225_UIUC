#include "Node.h"
#include <iostream>

using namespace std;

Node *listIntersection(Node *first, Node *second) {
  // your code here
  if (first == NULL || second == NULL) {
    return NULL;
  }
  Node* head = NULL;
  Node* curr = head;
  int count = 0;
  for (Node* i = first; i != NULL; i = i->next_) {
    for (Node* j = second; j!=NULL;j = j->next_) {
      bool control = false;
      if (i->data_ == j->data_) {
        if (count == 0) {
          head = new Node(*i);
          //head->data_ = i->data_;
          head->next_ = NULL;
          curr = head;
          count++;
          continue;
        }
        for (Node* k = head; k != NULL; k = k->next_) {
          if (k->data_ == i->data_) {
            control = true;
            break;
          }
        }
        if (control == true) {
          continue;
        }
        curr->next_ = new Node(*i);
        //curr->next_->data_ = i->data_;
        curr = curr->next_;
        curr->next_ = NULL;
        count++;
        break;
      }
    }
  }
  if (count == 0) {
    return NULL;
  }
  return head;
}

Node::Node() {
    numNodes++;
}

Node::Node(Node &other) {
    this->data_ = other.data_;
    this->next_ = other.next_;
    numNodes++;
}

Node::~Node() {
    numNodes--;
}

int Node::numNodes = 0;
