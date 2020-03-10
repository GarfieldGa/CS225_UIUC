#include "Node.h"

using namespace std;

Node *listSymmetricDifference(Node *first, Node *second) {
  // your code here
  if (first == NULL && second == NULL) {
    return NULL;
  }
  Node* head = NULL;
  Node* curr = head;
  for (Node* fr = first; fr != NULL; fr = fr->next_) {
    bool control = false;
    for (Node* sec = second; sec != NULL; sec = sec->next_) {
      if (fr->data_ == sec->data_) {
        control = true;
      }
    }
    if (!control) {
      if (head == NULL) {
        head = new Node(*fr);
        head->next_ = NULL;
        curr = head;
        continue;
      }
      bool ct = false;
      for (Node* i = head; i != NULL; i = i->next_) {
        if (fr->data_ == i->data_) {
          ct = true;
          break;
        }
      }
      if (ct) {
        continue;
      }
      curr->next_ = new Node(*fr);
      curr = curr->next_;
      curr->next_ = NULL;
    }
  }
  for (Node* sec = second; sec != NULL; sec = sec->next_) {
    bool control = false;
    for (Node* fr = first; fr != NULL; fr = fr->next_) {
      if (fr->data_ == sec->data_) {
        control = true;
      }
    }
    if (!control) {
      if (head == NULL) {
        head = new Node(*sec);
        head->next_ = NULL;
        curr = head;
        continue;
      }
      bool ct = false;
      for (Node* i = head; i != NULL; i = i->next_) {
        if (sec->data_ == i->data_) {
          ct = true;
          break;
        }
      }
      if (ct) {
        continue;
      }
      curr->next_ = new Node(*sec);
      curr = curr->next_;
      curr->next_ = NULL;
    }
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
