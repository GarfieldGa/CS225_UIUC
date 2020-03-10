#include "Derived.h"
#include "Base.h"
#include <string>

Derived::~Derived(){}
std::string Derived::foo() {
  return "I will not eat them.";
}
std::string Derived::bar() {
  return "And Ham";
}
