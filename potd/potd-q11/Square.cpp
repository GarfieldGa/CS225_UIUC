#include <iostream>
#include <string>

#include "Square.h"

Square::Square() {
    name = "mysquare";
    lengthptr = new double;
    *lengthptr = 2.0;
}

std::string Square::getName() const {
  return name;
}

double Square::getLength() const {
  return *lengthptr;
}

Square::Square(const Square & other) {
    name = other.getName();
    lengthptr = new double;
    *lengthptr = other.getLength();
}

Square::~Square() {
    delete lengthptr;
}

Square & Square::operator=(const Square & other) {
  this->setName(other.getName());
  this->setLength(other.getLength());
  return *this;
}

Square Square::operator+(const Square & other) {
  Square* newSquare = new Square();
  std::string newName = this->getName() + other.getName();
  int newLength = this->getLength() + other.getLength();
  newSquare->setName(newName);
  newSquare->setLength(newLength);
  return *newSquare;
}

void Square::setName(std::string newName) {
  name = newName;
}

void Square::setLength(double newVal) {
  *lengthptr = newVal;
}
