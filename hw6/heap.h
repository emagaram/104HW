#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T>>
class Heap
{
public:
  /// Constructs an m-ary heap for any m >= 2
  Heap(int m, PComparator c = PComparator());

  /// Destructor as needed
  ~Heap();

  /// Adds an item
  void push(const T &item);

  /// returns the element at the top of the heap
  ///  max (if max-heap) or min (if min-heap)
  T const &top() const;

  /// Removes the top element
  void pop();

  /// returns true if the heap is empty
  bool empty() const;

private:
  /// Add whatever helper functions and data members you need below
  int _m;
  size_t _effsize;
  PComparator _pc;
  std::vector<T> data;
  void heapify(size_t loc);
  void trickleUp(size_t loc);
};

// Add implementation of member functions here
template <typename T, typename PComparator>
void Heap<T, PComparator>::heapify(size_t loc)
{
  if (_m * loc + 1 >= _effsize)
  {
    return;
  }
  size_t bestChild = _m * loc + 1; // start w/ left

  for (int i = 2; i <= _m; i++) //runs m-1 times since we have leftmost. From 2 -> m
  {
    if (_m * loc + i < _effsize) //node exists
    {
      size_t rChild = _m * loc + i;
      if (_pc.operator()(data[rChild], data[bestChild]))
      {
        bestChild = rChild;
      }
    }
  }

  if (_pc.operator()(data[bestChild], data[loc]))
  {
    std::swap(data[loc], data[bestChild]);
    heapify(bestChild);
  }
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::trickleUp(size_t loc)
{
  // could be implemented recursively
  size_t parent = (loc - 1) / _m;
  if (parent <= _effsize - 1 && parent!=loc)
  {
    while (parent >= 0 &&
           _pc.operator()(data[loc], data[parent]))
    {
      std::swap(data[parent], data[loc]);
      loc = parent;
      if(loc==0){
        break;
      }
      parent = (loc - 1) / _m;
    }
  }
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T &item)
{
  data.push_back(item);
  _effsize++;
  trickleUp(_effsize-1);
}

// We will start top() for you to handle the case of
// calling top on an empty heap
template <typename T, typename PComparator>
T const &Heap<T, PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if (empty())
  {
    throw std::logic_error("can't top an empty heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return data[0];
}

// We will start pop() for you to handle the case of
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T, PComparator>::pop()
{
  if (empty())
  {
    throw std::logic_error("can't pop an empty heap");
  }
  data[0] = *(data.begin() + _effsize-1);
  data.erase(data.begin() + _effsize-1);
  _effsize--;
  heapify(0);
}

template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const
{
  if (data.empty())
  {
    return true;
  }
  return false;
}

template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c)
{
  _m = m;
  _pc = c;
  _effsize = 0;
}
template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap()
{
}

#endif
