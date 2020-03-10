// Your code here
#include <string>
#include "Food.h"

using namespace std;

Food::Food() {
}
string Food::get_name() {
  return name_;
}
void Food::set_name(string n) {
  name_ = n;
}
int Food::get_quantity(){
  return quantity_;
}
void Food::set_quantity(int q) {
  quantity_ = q;
}
