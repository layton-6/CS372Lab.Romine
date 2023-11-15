// William Romine
// 00103649
// Dr. Lewis CS372

// Helpful article for me when using partitions https://www.geeksforgeeks.org/partition_point-in-cpp/

#include <iostream>
#include <list>
#include <algorithm>

template<typename T>
std::list<T> quicksort(std::list<T> inputList)
{
    if(inputList.size() <= 1)
    {
        return inputList;
    }

    T splittingValue = inputList.front();
    inputList.pop_front();

    auto partitionPoint = std::partition(inputList.begin(), inputList.end(), [splittingValue](const T& element){
        return element < splittingValue;
    });

    std::list<T> lessThanList(inputList.begin(), partitionPoint);
    std::list<T> greaterThanList(partitionPoint, inputList.end());

    std::list<T> result;
    result.splice(result.end(), quicksort(lessThanList));
    result.push_back(splittingValue);
    result.splice(result.end(), quicksort(greaterThanList));

    return result;
}

int main()
{
    std::list<int> inputList = {3, 2, 8, 6, 4, 4, 2, 1, 8, 9, 7, 5};

    std::list<int> sortedList = quicksort(inputList);

    std::cout << "Sorted List: ";
    for (const auto& element : sortedList)
    {
        std::cout << element << " ";
    }

    return 0;
}

