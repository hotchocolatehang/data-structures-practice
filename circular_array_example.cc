#include <iostream>
#include <algorithm>

#include "cobsea_libs/circular_array.h"

using namespace cobsea_libs;

template <typename T>
void PrintContainerSizeState(T &arr)
{
  std::cout << "Container's capacity: " << arr.Capacity()
            << "; size: " << arr.Size() 
            << "; unused: " << arr.Capacity() - arr.Size()
            << "." << std::endl;
};

template <typename T>
void PrintCircularArray(CircularArray<T> arr)
{
  std::for_each(arr.begin(), arr.end(), [](auto x) {
    std::cout << x << " ";
  });
  std::cout << std::endl;
  PrintContainerSizeState(arr);
};

int main() {
  // Available constructors:
  // CircularArray<int> circular_array;
  // CircularArray<float> circular_array(6);
  CircularArray<double> circular_array(8, 9.6);

  circular_array.PushBack(5);
  circular_array.PushFront(4);
  circular_array.PushBack(6);
  circular_array.PopFront();
  circular_array.PopBack();

  std::cout << "circular_array.Front() = " << circular_array.Front() << "\n"
            << "circular_array.Back() = " << circular_array.Back() << "\n"
            << std::endl;
  std::cout << "Elements of the circular_array:\n";
  for (size_t i = 0; i < circular_array.Size(); i++)
    std::cout << "circular_array.[" << i << "] = " << circular_array[i] << "\n";

  std::cout << "\n";
  PrintContainerSizeState(circular_array);
  PrintCircularArray(circular_array);

  return 0;
}