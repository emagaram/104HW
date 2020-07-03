#include <stdexcept>
template <typename T, typename Comparator>
void heapify(std::vector<T> &data, size_t loc, size_t effsize, Comparator &c)
{
    if (2 * loc > effsize)
        return;
    size_t smallerChild = 2 * loc; // start w/ left
    if (2 * loc + 1 <= effsize)
    {
        size_t rChild = smallerChild + 1;
        if (c.operator()(data[rChild], data[smallerChild]))
        {
            smallerChild = rChild;
        }
    }

    if (c.operator()(data[smallerChild], data[loc]))
    {
        std::swap(data[loc], data[smallerChild]);
        heapify(data, smallerChild, effsize, c);
    }
}

template <typename T>
T const top(std::vector<T> &data)
{
    if (data.empty())
    {
        throw(std::out_of_range("empty"));
    }
    return data[1];
}

template <typename T, typename Comparator>
void pop(std::vector<T> &data,  Comparator &c)
{
    if (data.empty())
    {
        throw(std::out_of_range("empty"));
    }
    data[1] = data.back();
    data.pop_back();
    heapify(data, 1, data.size()-1, c);
}



template <typename T, typename Comparator>
void hsort(std::vector<T> &data, Comparator c = Comparator())
{
    size_t heapSize = data.size() - 1;
    //n loops, logn operations
    for (size_t i = heapSize; i >= 1; i--)
    {
        heapify(data, i, heapSize, c);
    }

    size_t sortedPoint = heapSize;
    //Puts vector in reverse order of what it should be
    //N loops, constant operations
    while(sortedPoint>0){
        T temp = top(data);
        pop(data, c);
        data[sortedPoint]=temp;
        sortedPoint--;
    }
    //N loops, constant operations
    for (size_t i = 1; i <heapSize/2+1;i++){
        std::swap(data[i],data[heapSize+1-i]);
    }

}