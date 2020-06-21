#ifndef DEQUE_H
#define DEQUE_H
#include <stdexcept>

/**
 * Implements a templated, array-based, 
 * double-ended queue.
 *
 * The Deque should allow for amortized O(1) 
 * insertion and removal from either end. 
 * It should dynamically resize, when it becomes
 * full, but never needs to shrink.  
 *
 * It should use a circular buffer approach
 * by tracking the "front" and "back" location.
 */

template <typename T>
class Deque
{
public:
   /* START - DO NOT CHANGE ANY OF THESE LINES */
   /**
   *  Default constructor 
   *   Create an array of size 1 by default
   */
   Deque();

   /**
   *  Default constructor 
   *   Create an array of the given capacity.
   */
   Deque(size_t capacity);

   /**
   *  Destructor
   */
   ~Deque();

   /**
   *  Returns the number of elements in the Deque. 
   *   - Must run in O(1)
   */
   size_t size() const;

   /**
   *  returns true if the deque is empty
   *   - Must run in O(1)
   */
   bool empty() const;

   /**
   *  returns  the i-th element from the front
   *   - Must run in O(1)
   *   - Must throw std::range_error if i is
   *      an invalid location
   */
   T &operator[](size_t i);

   /**
   *  returns  the i-th element from the front
   *   - Must run in O(1)
   *   - Must throw std::range_error if i is
   *      an invalid location
   */
   T const &operator[](size_t i) const;

   /**
   *  Inserts a new item at the back of the
   *  Deque
   *   - Must run in amortized O(1)
   */
   void push_back(const T &item);

   /**
   *  Inserts a new item at the front of the
   *  Deque
   *   - Must run in amortized O(1)
   */
   void push_front(const T &item);

   /**
   *  Removes the back item from the Deque
   *   - Must run in amortized O(1)
   *   - Simply return if the deque is empty
   */
   void pop_back();

   /**
   *  Removes the front item from the Deque
   *   - Must run in amortized O(1)
   *   - Simply return if the deque is empty
   */
   void pop_front();
   /* END - DO NOT CHANGE ANY OF THESE LINES */
private:
   /* Add data members and private helper 
   * functions below 
   */

   //increase deque size by N. In so doing, we will have
   //an amortized runtime of O(1) because in an empty array 1/N operations will take
   //O(n) time and the rest of the N-1 operations will take O(1) time. The O(n) operation
   //will only occur at most 1/n times assuming no deletes occur.
   void doubleArraySize();

   T *_elements;
   size_t _head;
   size_t _tail;
   size_t _size;
   size_t _MAX;
};

/* Implement each Deque<T> member function below 
 * taking care to meet the runtime requirements
 */
template <typename T>
Deque<T>::Deque()
{
   _elements = new T[1];
   _head = 0;
   _tail = 0;
   _size = 0;
   _MAX = 1;
}

template <typename T>
Deque<T>::~Deque()
{
   delete[] _elements;
}

template <typename T>
Deque<T>::Deque(size_t capacity)
{
   _elements = new T[capacity];
   _MAX = capacity;
   _size = 0;
   _head = 0;
   _tail = 0;
}

template <typename T>
void Deque<T>::doubleArraySize()
{
   T *newElements = new T[2 * _MAX];
   size_t index = _head; //Start at head and go until tail-1 which
   //is head+size. All items indexed will have something in them
   for (size_t i = 0; i < _size; i++)
   {
      newElements[i] = _elements[index];
      index = (index + 1) % _MAX;
   }
   delete[] _elements;
   _MAX *= 2;
   _elements = newElements;
   _head = 0;
   _tail = _size;
}

template <typename T>
void Deque<T>::push_back(const T &item)
{
   if (_size + 1 >= _MAX)
   {
      //The +1 is needed since the tail points at an empty item
      //And there needs to be a space for it to move to after filling
      //A slot
      doubleArraySize();
   }
   _elements[_tail] = item;
   _tail = (_tail + 1) % _MAX;
   _size++;
}

template <typename T>
void Deque<T>::push_front(const T &item)
{
   if (_size + 1 >= _MAX)
   {
      //The +1 is needed since the head needs room to move
      doubleArraySize();
   }
   if (_head == 0)
   {
      _head = _MAX - 1;
   }
   else
   {
      _head--;
   }
   _elements[_head] = item;
   _size++;
}

template <typename T>
void Deque<T>::pop_back()
{
   if (!empty())
   {
      if (_tail == 0)
      {
         _tail = _MAX - 1;
      }
      else
      {
         _tail--;
      }
      _size--;
   }
}

template <typename T>
void Deque<T>::pop_front()
{
   if (!empty())
   {
      _head=(_head+1)%_MAX;
      _size--;
   }
}

template <typename T>
T &Deque<T>::operator[](size_t i)
{

   if (i < 0 || i >= _size)
   {
      throw std::range_error("Index is out of range");
   }
   else
   {
      return _elements[(_head + i) % _MAX];
   }
}

template <typename T>
T const &Deque<T>::operator[](size_t i) const
{
   if (i < 0 || i >= _size)
   {
      throw std::range_error("Index is out of range");
   }
   else
   {
      return _elements[(_head + i) % _MAX];
   }
}

template <typename T>
bool Deque<T>::empty() const
{
   if (_size == 0)
   {
      return true;
   }
   return false;
}

template <typename T>
size_t Deque<T>::size() const
{
   return _size;
}

#endif
