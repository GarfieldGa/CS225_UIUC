// Animal.h
#pragma once
#include <string>

class Animal {
public:
  Animal();
  Animal(std::string type, std::string food);
  std::string getType();
  void setType(std::string type);
  virtual std::string getFood();
  virtual void setFood(std::string food);
  virtual std::string print();
private:
  std::string type_;
  std::string food_;
};
