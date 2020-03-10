// your code here
#include "Food.h"
#include "q5.h"
#include <string>
#include <iostream>
using namespace std;

int main() {
  Food* food = new Food();
  q5* qq = new q5();
  food->set_name("Pineapples");
  food->set_quantity(4);
  std::cout <<"You have "<<food->get_quantity()<<food->get_name()<<"."<<endl;
  qq->increase_quantity(food);
  std::cout <<"You have "<<food->get_quantity()<<food->get_name()<<"."<<endl;
  delete food;
  delete qq;
}
