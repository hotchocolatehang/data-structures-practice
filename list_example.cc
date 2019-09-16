#include <iostream>
#include <algorithm>
#include "cobsea_libs/list.h"
using namespace cobsea_libs;

template<typename T>
void PrintList(List<T> l) {
  std::for_each(l.begin(), l.end(), [](auto x) {
    std::cout << x << " ";
  });
  std::cout << std::endl;
}

int main() {
  List<double> list (8, 3);
  list.PushBack(2.7);
  list.PushFront(2.6);
  list[0] = 2.8;
  list.RemoveAt(9);

  PrintList(list);

  return 0;
}