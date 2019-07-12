#include <iostream>

#include "list/list.h"
#include "construct_test_class/construct_test_class.h"
using namespace hotchocolatehang_libs;

template<typename T>
void PrintList(List<T> l) {
  for (size_t i = 0; i < l.Size(); i++)
    std::cout << l[i] << " ";
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