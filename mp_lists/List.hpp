/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
*/

template <class T>
List<T>::List() {
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  for (ListNode* current = head_; current != NULL; current = current) {
    if (current->next == NULL) {
      delete current;
      break;
    }
    current = current->next;
    delete current->prev;
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  if (head_ == NULL) {
    head_ = newNode;
    tail_ = newNode;
  } else {
    newNode -> next = head_;
    head_->prev = newNode;
    head_ = newNode;
  }
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  if (tail_ == NULL) {
    head_ = newNode;
    tail_ = newNode;
  } else {
    newNode->prev = tail_;
    tail_->next = newNode;
    tail_ = newNode;
  }
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode * curr = start;
  if (splitPoint >= length_) {
    return NULL;
  }
  if (splitPoint <= 0) {
    return head_;
  }
  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }
  if (curr != NULL) {
    curr->prev->next = NULL;
    curr->prev = NULL;
  }
  return curr;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  int count = 1;
  for (ListNode* current = head_; current != NULL; current = current->next) {
    if (count%2 == 0) {
      if (current->next == NULL) {
        break;
      }
      ListNode* tmp = current;
      tmp->prev->next = tmp->next;
      current = tmp->prev;
      tmp->next->prev = tmp->prev;
      tmp->prev = tail_;
      tail_->next = tmp;
      tmp->next = NULL;
      tail_ = tmp;
    }
    count++;
  }
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  if (startPoint == NULL || endPoint == NULL || startPoint == endPoint) {
    return;
  }
  ListNode* old_end = endPoint->next;
  for (ListNode* curr = startPoint; curr != old_end; curr = curr->prev) {
    if (curr == NULL) {
      break;
    }
    ListNode* tmp = curr->next;
    curr->next = curr->prev;
    curr->prev = tmp;
  }
  ListNode* temp = startPoint;
  startPoint = endPoint;
  endPoint = temp;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  if (n <= 1) {
    return;
  }
  if (head_ == NULL) {
    return;
  }
  if (n >= length_) {
    reverse(head_, tail_);
    return;
  }
  int gp = length_/n;
  ListNode* start = head_;
  ListNode* end = NULL;
  for (int i = 0; i < gp; i++) {
    ListNode* prev_end = end;
    end = start;
    for (int j = 0; j < n-1; j++) {
      end = end->next;
    }
    if (prev_end != NULL) {
      prev_end->next = end;
    }
    reverse(start, end);
    if (i == 0) {
      head_ = start;
    }
    ListNode* tmp = start;
    start = start->prev;
    tmp->prev = prev_end;
  }
  if (start != NULL) {
    reverse(start, tail_);
    start->prev = end;
    end->next = start;
  } else {
    tail_ = end;
  }
  head_->prev = NULL;
  tail_->next = NULL;
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if (first == NULL) {
    return second;
  }
  if (second == NULL) {
    return first;
  }
  ListNode* sec = NULL;
  ListNode* fr = NULL;
  ListNode* start = NULL;
  if (first->data < second->data) {
    start = first;
    fr = first->next;
    sec = second;
  } else {
    start = second;
    fr = first;
    sec = second->next;
  }
  ListNode* curr = start;
  while(fr != NULL || sec != NULL) {
    if (sec == NULL) {
      curr->next = fr;
      fr = fr->next;
      curr->next->prev = curr;
      curr = curr->next;
      continue;
    }
    if (fr == NULL) {
      curr->next = sec;
      sec = sec->next;
      curr->next->prev = curr;
      curr = curr->next;
      continue;
    }
    if (fr->data < sec->data) {
      curr->next = fr;
      fr->prev = curr;
      fr = fr->next;
      curr = curr->next;
    } else {
      curr->next = sec;
      sec->prev = curr;
      sec = sec->next;
      curr = curr->next;
    }
  }
  return start;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (chainLength <= 1) {
    return start;
  }
  ListNode* secondList = split(start, chainLength/2);
  return merge(mergesort(start, chainLength/2), mergesort(secondList, chainLength - (chainLength/2)));
}
