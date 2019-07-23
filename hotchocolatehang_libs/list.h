#ifndef HOTCHOCOLATEHANG_LIBS_LIST_H_
#define HOTCHOCOLATEHANG_LIBS_LIST_H_

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
  List(List const& other);
  List(List const&& other);
  ~List();

  void PushFront(ValueType _val);
  void PushBack(ValueType _val);
  void PopFront();
  void PopBack();
  ValueType& Front() const;
  ValueType& Back() const;
  void InsertAt(ValueType _val, size_t _pos);
  void RemoveAt(size_t _pos);

  bool Empty() const;
  size_t Size() const;

  ValueType& operator[](size_t _index) const;

  class iterator : public std::iterator<std::bidirectional_iterator_tag, ValueType>
  {
  public:
    friend class List<ValueType>;
    ListNode<ValueType> *curr;

    typedef ValueType value_type;
    typedef ValueType& reference;
    typedef ValueType* pointer;
    typedef ValueType difference_type;
    typedef std::bidirectional_iterator_tag iterator_category;

    iterator (ListNode<ValueType> *x) : 
      curr (x)
    {

    };

    bool operator== (iterator const& other) const 
    {
      return curr == other.curr;
    };

    bool operator!= (iterator const& other) const 
    {
      return curr != other.curr;
    };

    reference operator*() const 
    {
      return curr->value;
    };

    iterator& operator++() 
    {
      curr = curr->next;
      return *this;
    };

    iterator& operator++(int) 
    {
      iterator tmp(curr);
      curr = curr->next;
      return tmp;
    };

    iterator& operator--() 
    {
      curr = curr->prev;
      return *this;
    };

    iterator& operator--(int) 
    {
      iterator tmp(curr);
      curr = curr->prev;
      return tmp;
    };
  };

  iterator begin()
  {
    return iterator(head_);
  };

  iterator end() 
  {
    return iterator(nullptr);
  };

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
  head_->value = _val;
  ListNode<ValueType> *temp_next;
  for (size_t i = 1; i < _size; i++, tail_ = temp_next) {
    temp_next = new ListNode<ValueType>;
    temp_next->value = _val;
    tail_->next = temp_next;
    temp_next->prev = tail_;
  }
};

template <typename ValueType>
List<ValueType>::List(List const& other) :
  List (other.size_)
{
  ListNode<ValueType> *source = other.head_,
                      *target = head_;
  for (; source != nullptr; target = target->next, source = source->next)
    target->value = source->value;
};

template <typename ValueType>
List<ValueType>::List(List const&& other) :
  head_ (other.head_),
  tail_ (other.tail_),
  size_ (other.size_)
{
  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.size_ = 0;
};

template <typename ValueType>
List<ValueType>::~List()
{
  if (tail_ != nullptr)
    for (tail_ = tail_->prev; tail_ != nullptr; tail_ = tail_->prev)
      delete tail_->next;
  if (head_ != nullptr)
    delete head_;
};

template <typename ValueType>
void List<ValueType>::PushFront(ValueType _val)
{
  ListNode<ValueType> *new_element = new ListNode<ValueType>;
  new_element->value = _val;
  new_element->next = head_;
  new_element->prev = nullptr;
  if (head_ != nullptr)
    head_->prev = new_element;
  head_ = new_element;
  if (tail_ == nullptr)
    tail_ = new_element;
  size_++;
};

template <typename ValueType>
void List<ValueType>::PushBack(ValueType _val)
{
  ListNode<ValueType> *new_element = new ListNode<ValueType>;
  new_element->value = _val;
  new_element->next = nullptr;
  new_element->prev = tail_;
  if (tail_ != nullptr)
    tail_->next = new_element;
  tail_ = new_element;
  if (head_ == nullptr)
    head_ = new_element;
  size_++;
};

template <typename ValueType>
void List<ValueType>::PopFront()
{
  ListNode<ValueType> *old_head = head_;
  if (head_ == tail_) {
    head_ = tail_ = nullptr;
  }
  else {
    head_ = head_->next;
    head_->prev = nullptr;
  }
  delete old_head;
  size_--;
};

template <typename ValueType>
void List<ValueType>::PopBack()
{
  ListNode<ValueType> *old_tail = tail_;
  if (head_ == tail_) {
    head_ = tail_ = nullptr;
  }
  else {
    tail_ = tail_->prev;
    tail_->next = nullptr;
  }
  delete old_tail;
  size_--;
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
  if (_pos > 0)
    for (size_t i = 0; i < _pos - 1; i++)
      prev_insert = prev_insert->next;
  new_element->prev = prev_insert;
  new_element->next = prev_insert->next;
  prev_insert->next = new_element;
  new_element->next->prev = new_element;
  size_++;
};

template <typename ValueType>
void List<ValueType>::RemoveAt(size_t _pos)
{
  ListNode<ValueType> *to_delete = head_;
  for (size_t i = 0; i < _pos; i++)
    to_delete = to_delete->next;
  if (to_delete == head_)
    head_ = head_->next;
  else if (to_delete == tail_)
    tail_ = tail_->prev;
  
  // awful code, I believe it can be expressed in a smarter way:
  if (to_delete->prev != nullptr) {
    to_delete->prev->next = to_delete->next;
  }
  else {
    if (to_delete->next != nullptr)
      to_delete->next->prev = nullptr;
  }

  if (to_delete->next != nullptr) {
    to_delete->next->prev = to_delete->prev;
  }
  else {
    if (to_delete->prev != nullptr)
      to_delete->prev->next = nullptr;
  }

  delete to_delete;
  size_--;
};

template <typename ValueType>
size_t List<ValueType>::Size() const
{
  return size_;
};

template <typename ValueType>
bool List<ValueType>::Empty() const
{
  return size_ == 0;
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