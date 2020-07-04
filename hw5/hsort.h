#ifndef HSORT_H
#define HSORT_H
#include <stdexcept>
#include <iterator>
template <typename T, typename Comparator>
void heapify(std::vector<T> &data, size_t loc, size_t effsize, Comparator &c)
{
    if (2 * loc > effsize)
        return;
    size_t smallerChild = 2 * loc; // start w/ left
    if (2 * loc + 1 <= effsize)
    {
        size_t rChild = smallerChild + 1;
        if (c.operator()(data[smallerChild], data[rChild]))
        {
            smallerChild = rChild;
        }
    }

    if (c.operator()(data[loc], data[smallerChild]))
    {
        std::swap(data[loc], data[smallerChild]);
        heapify(data, smallerChild, effsize, c);
    }
}

template <typename T>
T const top(std::vector<T> &data)
{
    if (data.empty()||data.size()==1)
    {
        throw(std::out_of_range("empty"));
    }
    return data[1];
}

template <typename T, typename Comparator>
void pop(std::vector<T> &data,  Comparator &c, size_t effsize)
{
    if (data.empty()||data.size()==1)
    {
        throw(std::out_of_range("empty"));
    }
    data[1] = *(data.begin()+effsize);
    data.erase(data.begin()+effsize);
    heapify(data, 1, effsize-1, c);
}



template <typename T, typename Comparator>
void hsort(std::vector<T> &data, Comparator c = Comparator())
{
    T emptyItem;
    data.insert(data.begin(),emptyItem); //so that index 0 is empty
    size_t heapSize = data.size() - 1;
    //n loops, logn operations
    for (size_t i = heapSize; i >= 1; i--)
    {
        heapify(data, i, heapSize, c);
    }

    //Puts vector in reverse order of what it should be
    //N loops, constant operations
    while(heapSize!=0){
        T temp = top(data);
        pop(data, c, heapSize);        
        data.insert(data.begin()+heapSize, temp);        
        heapSize--;
    }
    //N loops, constant operations
    for (size_t i = 1; i <heapSize/2+1;i++){
        std::swap(data[i],data[heapSize+1-i]);
    }
    data.erase(data.begin());
}
#endif