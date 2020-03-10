#pragma once
#include <string>
using namespace std;

class Food {
 public:
   Food();
   int get_quantity();
   void set_quantity(int q);
   string get_name();
   void set_name(string n);
 private:
   string name_;
   int quantity_;
};
