// your code here
# include "Bar.h"
# include <string>
# include <iostream>

potd::Bar::Bar(std::string name) {
  this->f_ = new potd::Foo(name);
}
potd::Bar::Bar(const potd::Bar &that) {
  const potd::Foo & ad1 = *that.f_;
  this->f_ = new potd::Foo(ad1);
}
potd::Bar::~Bar(){
  this->f_->~Foo();
}
potd::Bar& potd::Bar::operator=(const potd::Bar &that) {
  this->f_->~Foo();
  this->f_ = new potd::Foo(*that.f_);
  return *this;
}
std::string potd::Bar::get_name() {
  return this->f_->get_name();
}
