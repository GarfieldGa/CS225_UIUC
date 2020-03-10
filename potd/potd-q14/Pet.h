// Pet.h
#pragma once
#include "Animal.h"
#include <string>

class Pet : public Animal {
private:
  std::string name_;
  std::string owner_name_;
public:
  std::string getName();
  std::string getFood();
  std::string getOwnerName();
  void setName(std::string n);
  void setFood(std::string f);
  void setOwnerName(std::string o);
  std::string print();
  Pet();
  Pet(std::string a, std::string f, std::string n, std::string o);
};
