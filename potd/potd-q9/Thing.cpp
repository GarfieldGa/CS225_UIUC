// Your code here!
#include "Thing.h"
#include <string>
namespace potd {
  Thing::Thing(int size){
    props_max = size;
  }
  Thing(const Thing & other) {
    this->properties_ = other.get_property();
    this->*values_ = other.get_values_;
  }
  Thing & operator=(const Thing & other);
  ~Thing();

  int set_property(std::string name,std::string value);
  std::string get_property(std::string name);
  void _copy(const Thing & other);
  void _destroy();
}
