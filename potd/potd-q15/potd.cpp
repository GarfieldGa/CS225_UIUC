#include "potd.h"
#include <iostream>

using namespace std;

string stringList(Node *head) {
    // your code here!
    if (head == NULL) {
      return "Empty list";
    }
    std::string out = "Node 0: " + to_string(head->data_);
    int count = 1;
    if (head->next_ == NULL) {
      return out;
    }
    for (Node* i = head->next_; i != NULL; i = i->next_) {
      out += " -> Node " + to_string(count) + ": " + to_string(i->data_);
      count++;
    }
    return out;
}
