// your code here!
#include "potd.h"
#include <cmath>
#include <iostream>

namespace potd {
  int* raise(int* arr) {
    unsigned int n = 1;
    for (int i = 0; *(arr+i) > 0; i++) {
      n++;
    }
    int* arr2 = new int[n];
    for (unsigned int i = 0; i < n; i++) {
      *(arr2+i) = *(arr+i);
    }
    if (n < 2) {
      return arr2;
    } else {
      for (unsigned int i = 0; i < n - 2; i++) {
        *(arr2+i) = pow(*(arr+i), *(arr + (i+1)));
      }
    }
    return arr2;
  }
}
