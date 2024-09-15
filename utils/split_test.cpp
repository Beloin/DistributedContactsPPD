#include "split.cpp"
#include "split.hpp"
#include <iostream>
#include <string>

template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
  os << "[";
  for (typename std::vector<T>::const_iterator ii = v.begin(); ii != v.end();
       ++ii) {
    os << " " << *ii;
  }
  os << " ]";
  return os;
}
int main() {
  std::string str{"Hello,myname,is,slimshady"};
  auto res = split(str, ",");
  std::cout << "Hi: " << res;
}
