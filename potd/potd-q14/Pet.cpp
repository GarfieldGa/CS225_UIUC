// Pet.cpp
#include "Pet.h"
#include <string>

std::string Pet::getName() {
  return name_;
}
std::string Pet::getFood() {
  return food_;
}
std::string Pet::getOwnerName() {
  return owner_name_;
}
void Pet::setName(std::string n) {
  name_ = n;
}
void Pet::setFood(std::string f) {
  food_ = f;
}
void Pet::setOwnerName(std::string o) {
  owner_name_ = o;
}
std::string Pet::print() {
  return "My name is " + name_;
}
Pet::Pet() {
  this->setType("cat");
  food_ = "fish";
  name_ = "Fluffy";
  owner_name_ = "Cinda";
}
Pet::Pet(std::string a, std::string f, std::string n, std::string o) {
  this->setType(a);
  food_ = f;
  name_ = n;
  owner_name_ = o;
}
