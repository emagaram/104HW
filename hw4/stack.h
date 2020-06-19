#ifndef STACK_H
#define STACK_H
#include <stdexcept>
#include "deque.h"

/** 
 * Your Stack<T> class must be templated and
 * privately inherit from Deque<T>. All
 * operations must run in O(1).
 *
 * Both pop() and top() must throw std::underflow_error
 * if the stack is empty.
 */

template <typename T>
class Stack : private Deque<T>
{
 public:
  Stack();
  size_t size() const;
  bool empty() const;
  void push(const T& item);
  void pop();
  T const & top() const;
};

#endif
