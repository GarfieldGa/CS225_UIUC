#pragma once
#include <string>

class Base {
public:
  virtual ~Base();
  std::string foo();
  virtual std::string bar();
};
