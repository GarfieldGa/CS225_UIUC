/* Your code here! */
#include "dsets.h"
#include <iostream>

void DisjointSets::addelements(int num) {
  for (int i = 0; i < num; i++) {
    set.push_back(-1);
  }
}

int DisjointSets::find(int elem) {
  if (set[elem] < 0) {
    return elem;
  }
  int idx = find(set[elem]);
  set[elem] = idx;
  return idx;
}

void DisjointSets::setunion(int a, int b) {
  int a1 = find(a);
  int b1 = find(b);
  if (set[a1] - set[b1] > 0) {
    int num = set[a1];
    set[a1] = b1;
    set[b1] += num;
  } else {
    int num = set[b1];
    set[b1] = a1;
    set[a1] += num;
  }
}

int DisjointSets::size(int elem) {
  return -set[find(elem)];
}

void DisjointSets::printArr() {
  for (unsigned int i = 0; i < set.size(); i++) {
    std::cout<<i<<":"<<set[i]<<" ";
  }
}
