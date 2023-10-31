// William Romine
// 00103649
// Dr. Lewis CS372

// Helpful article for me to grasp concept of sorting in c++ stl. https://www.geeksforgeeks.org/sort-algorithms-the-c-standard-template-library-stl/#

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

template <typename T>
void QuickSort(std::vector<T>& arr, int left, int right) {
    if (left < right) {
        int pivot = left;
        int low = left;
        int high = right;

        while (low < high) {
            while (arr[low] <= arr[pivot] && low < right)
                low++;
            while (arr[high] > arr[pivot])
                high--;
            if (low < high)
                std::swap(arr[low], arr[high]);
        }

        std::swap(arr[pivot], arr[high]);
        QuickSort(arr, left, high - 1);
        QuickSort(arr, high + 1, right);
    }
}

template <typename T>
void MyQuickSort(std::vector<T>& arr) {
    QuickSort(arr, 0, arr.size() - 1);
}

int main() {
    std::vector<int> sizes = {100, 500, 1000, 5000, 10000};

    for (int size : sizes) {
        std::vector<int> data(size);
        std::vector<int> data_copy(size);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(1, 10000);

        // Fill the vectors with random integers
        for (int& num : data) {
            num = dis(gen);
        }
        data_copy = data; // Copy the data for std::sort()

        // Measure time for MyQuickSort
        auto start = std::chrono::high_resolution_clock::now();
        MyQuickSort(data);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "MyQuickSort for size " << size << ": " << duration.count() << " seconds" << std::endl;

        // Measure time for std::sort()
        start = std::chrono::high_resolution_clock::now();
        std::sort(data_copy.begin(), data_copy.end());
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        std::cout << "std::sort() for size " << size << ": " << duration.count() << " seconds" << std::endl;

        // Check if the sorting is correct
        if (data == data_copy) {
            std::cout << "Sorting is correct!" << std::endl;
        } else {
            std::cout << "Sorting is incorrect!" << std::endl;
        }
    }

    return 0;
}
