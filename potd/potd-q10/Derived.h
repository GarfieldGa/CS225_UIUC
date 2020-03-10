#pragma once
#include "Base.h"
#include <string>

class Derived : public Base {
  public:
    virtual ~Derived();
    std::string foo();
    std::string bar();
};
