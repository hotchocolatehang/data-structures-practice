#ifndef HOTCHOCOLATEHANG_LIBS_LIST_H_
#define HOTCHOCOLATEHANG_LIBS_LIST_H_

// #include <cstdlib>

namespace hotchocolatehang_libs {

template <typename ValueType>
struct ListNode {
  ValueType value;
  ListNode *prev,
           *next;
};

template <typename ValueType>
class List {
public:
  List();
  explicit List(size_t _size);
  List(size_t _size, ValueType _val);
  ~List();

  void PushFront(ValueType _val);
  void PushBack(ValueType _val);
  void PopFront();
  void PopBack();
  ValueType& Front() const;
  ValueType& Back() const;
  void InsertAt(ValueType _val, size_t _pos);
  void RemoveAt(size_t _pos);

  size_t Size() const;

  ValueType& operator[](size_t _index) const;
private:
  ListNode<ValueType> *head_,
                      *tail_;
  size_t size_;
};

// Definitions

template <typename ValueType>
List<ValueType>::List() :
  head_ (nullptr),
  tail_ (nullptr),
  size_ (0)
{

};

template <typename ValueType>
List<ValueType>::List(size_t _size) :
  head_ (new ListNode<ValueType>),
  tail_ (nullptr),
  size_ (_size)
{
  head_->prev = nullptr;
  tail_ = head_;
  ListNode<ValueType> *temp_next;
  for (size_t i = 1; i < _size; i++, tail_ = temp_next) {
    temp_next = new ListNode<ValueType>;
    tail_->next = temp_next;
    temp_next->prev = tail_;
  }
};

template <typename ValueType>
List<ValueType>::List(size_t _size, ValueType _val) :
  head_ (new ListNode<ValueType>),
  tail_ (nullptr),
  size_ (_size)
{
  head_->prev = nullptr;
  tail_ = head_;
  ListNode<ValueType> *temp_next;
  for (size_t i = 1; i < _size; i++, tail_ = temp_next) {
    temp_next = new ListNode<ValueType>;
    temp_next->value = _val;
    tail_->next = temp_next;
    temp_next->prev = tail_;
  }
};

template <typename ValueType>
List<ValueType>::~List()
{
  for (tail_ = tail_->prev; tail_ != nullptr; tail_ = tail_->prev)
    delete tail_->next;
  delete head_;
};

template <typename ValueType>
void List<ValueType>::PushFront(ValueType _val)
{
  ListNode<ValueType> *new_element = new ListNode<ValueType>;
  new_element->value = _val;
  new_element->next = head_;
  new_element->prev = nullptr;
  head_ = new_element;
};

template <typename ValueType>
void List<ValueType>::PushBack(ValueType _val)
{
  ListNode<ValueType> *new_element = new ListNode<ValueType>;
  new_element->value = _val;
  new_element->next = nullptr;
  new_element->prev = tail_;
  tail_ = new_element;
};

template <typename ValueType>
void List<ValueType>::PopFront()
{
  ListNode<ValueType> *old_head = head_;
  head_ = head_->next;
  delete old_head;
};

template <typename ValueType>
void List<ValueType>::PopBack()
{
  ListNode<ValueType> *old_tail = tail_;
  tail_ = tail_->next;
  delete old_tail;
};

template <typename ValueType>
ValueType& List<ValueType>::Front() const
{
  return head_->value;
};

template <typename ValueType>
ValueType& List<ValueType>::Back() const
{
  return tail_->value;
};

template <typename ValueType>
void List<ValueType>::InsertAt(ValueType _val, size_t _pos)
{
  ListNode<ValueType> *new_element = new ListNode<ValueType>,
                      *prev_insert = head_;
  new_element->value = _val;
  for (size_t i = 0; i < _pos - 1; i++)
    prev_insert = prev_insert->next;
  new_element->prev = prev_insert;
  new_element->next = prev_insert->next;
  prev_insert->next = new_element;
  new_element->next->prev = new_element;
};

template <typename ValueType>
void List<ValueType>::RemoveAt(size_t _pos)
{
  ListNode<ValueType> *to_delete = head_;
  for (size_t i = 0; i < _pos; i++)
    to_delete = to_delete->next;
  to_delete->prev->next = to_delete->next;
  to_delete->next->prev = to_delete->prev;
  delete to_delete;
};

template <typename ValueType>
size_t List<ValueType>::Size() const
{
  return size_;
};

template <typename ValueType>
ValueType& List<ValueType>::operator[](size_t _index) const
{
  ListNode<ValueType> *target = head_;
  for (size_t i = 0; i < _index; i++)
    target = target->next;
  return target->value;
};

}; // namespace hotchocolatehang_libs

#endif // HOTCHOCOLATEHANG_LIBS_LIST_H_