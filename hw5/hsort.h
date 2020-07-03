
// template <typename T>
// void swap(std::vector<T> &data, size_t first, size_t second)
// {
//     T temp = data[first];
//     data[first] = data[second];
//     data[second] = temp;
// }

template <typename T, typename Comparator>
void heapify(std::vector<T> &data, size_t loc, size_t effsize, Comparator &c)
{
    if (2*loc > effsize)
        return;
    size_t smallerChild = 2 * loc; // start w/ left
    if (2*loc + 1 <= effsize)
    {
        size_t rChild = smallerChild + 1;
        if (c.operator()(data[rChild],  data[smallerChild])){
            smallerChild = rChild;
        }
    }

    if (c.operator()(data[smallerChild], data[loc]))
    {
        std::swap(data[loc], data[smallerChild]);
        heapify(data, smallerChild, effsize, c);
    }
}

template <typename T, typename Comparator>
void hsort(std::vector<T> &data, Comparator c = Comparator())
{
}