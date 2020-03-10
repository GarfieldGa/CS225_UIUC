// your code here
#include "q5.h"
#include <string>

void increase_quantity(Food* ptr) {
  int a = ptr->get_quantity();
  ptr->set_quantity(a + 1);
}
