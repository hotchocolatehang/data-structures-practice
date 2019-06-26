/**
 * Class CircularArray defines the data structure which can be used as a simple
 * array. Also it provides O(1) time for insertion at the front or back for
 * most time (O(n) in the worst case), O(1) for remove operation at the front 
 * or back.
 */

#ifndef HOTCHOCOLATEHANG_LIBS_CIRCULAR_ARRAY_H_
#define HOTCHOCOLATEHANG_LIBS_CIRCULAR_ARRAY_H_

namespace hotchocolatehang_libs {

template <typename ValueType>
class CircularArray {
public:
  CircularArray();

  /**
   * Allocates space for _capacity elements in CircularArray
   */
  CircularArray(size_t _capacity);

  /**
   * Stores _capacity elements in CircularArray with value _val.
   * Be careful with RAII classes
   */
  CircularArray(size_t _capacity, ValueType _val);

  ~CircularArray();

  void PushFront(ValueType _val);
  void PushBack(ValueType _val);

  /**
   * Removes the first element (no return)
   */
  void PopFront();

  /**
   * Removes the last element (no return)
   */
  void PopBack();

  /**
   * Returns the first element
   */
  ValueType Front();

  /**
   * Returns the last element
   */
  ValueType Back();

  /**
   * Returns number of elements in the container
   */
  size_t Size();

  /**
   * Returns size of the allocated array
   */
  size_t Capacity();

  /**
   * Gives access to any arbitrary element in the container
   */
  ValueType operator[](size_t _index);

private:
  void ExtandArray();

  static constexpr size_t kDefaultCapacity = 20;

  ValueType *data_array_;
  size_t head_,
         tail_,
         size_,
         capacity_;
}; // class CircularArray

// Definitions

template <typename ValueType>
CircularArray<ValueType>::CircularArray() :
  data_array_ (nullptr),
  head_ (0),
  tail_ (0),
  size_ (0),
  capacity_ (0)
{

};

template <typename ValueType>
CircularArray<ValueType>::CircularArray(size_t _capacity) :
  data_array_ (new ValueType[_capacity]),
  head_ (0),
  tail_ (0),
  size_ (0),
  capacity_ (_capacity)
{

};

template <typename ValueType>
CircularArray<ValueType>::CircularArray(size_t _capacity, ValueType _val) :
  data_array_ (new ValueType[_capacity]),
  head_ (0),
  tail_ (_capacity - 1),
  size_ (_capacity),
  capacity_ (_capacity)
{
  for (size_t i = 0; i < _capacity; i++)
    data_array_[i] = _val;
};

template <typename ValueType>
CircularArray<ValueType>::~CircularArray()
{
  if (data_array_ != nullptr)
    delete [] data_array_;
};

template <typename ValueType>
void CircularArray<ValueType>::PushFront(ValueType _val)
{
  if (size_ == capacity_) {
    ExtandArray();
  };
  if (head_ == 0)
    head_ = capacity_ - 1;
  else
    head_--;
  data_array_[head_] = _val;
  size_++;
};

template <typename ValueType>
void CircularArray<ValueType>::PushBack(ValueType _val)
{
  if (size_ == capacity_)
    ExtandArray();
  data_array_[tail_] = _val;
  tail_ = (tail_ + 1) % capacity_;
  size_++;
};

template <typename ValueType>
void CircularArray<ValueType>::PopFront()
{
  head_ = (head_ + 1) % capacity_;
  size_--;
};

template <typename ValueType>
void CircularArray<ValueType>::PopBack()
{
  if (tail_ == 0)
    tail_ = capacity_ - 1;
  else
    tail_--;
  size_--;
};

template <typename ValueType>
ValueType CircularArray<ValueType>::Front()
{
  return data_array_[head_];
};

template <typename ValueType>
ValueType CircularArray<ValueType>::Back()
{
  return data_array_[tail_ != 0 ? tail_ - 1 : capacity_ - 1];
};

template <typename ValueType>
size_t CircularArray<ValueType>::Size()
{
  return size_;
};

template <typename ValueType>
size_t CircularArray<ValueType>::Capacity()
{
  return capacity_;
};

template <typename ValueType>
ValueType CircularArray<ValueType>::operator[] (size_t _index)
{
  return data_array_[(head_ + _index) % capacity_];
};

template <typename ValueType>
void CircularArray<ValueType>::ExtandArray()
{
  if (capacity_ == 0)
    capacity_ = 1;
  ValueType *new_array = new ValueType[capacity_ * 2];
  for (size_t i = 0; i < size_; i++)
    new_array[i] = data_array_[(head_ + i) % capacity_];

  if (data_array_ != nullptr)
    delete [] data_array_;
  data_array_ = new_array;
  head_ = 0;
  tail_ = size_;
  capacity_ *= 2;
};

}; // namespace hotchocolatehang_libs

#endif // HOTCHOCOLATEHANG_LIBS_CIRCULAR_ARRAY_H_