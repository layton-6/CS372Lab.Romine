// William Romine
// 00103649
// Dr. Lewis CS372

// Helpul Source in understanding binary_search, lower_bound, and upper_bound: https://www.geeksforgeeks.org/binary-search-functions-in-c-stl-binary_search-lower_bound-and-upper_bound/#

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
bool binarySearch(std::vector<T> aSortedVector, T itemToBeFound, bool printDebugData = false) {
    int comparisons = 0; //Set to 0 to keep track of number of comparisons.
    int right = aSortedVector.size() - 1;
    int left = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (aSortedVector[mid] == itemToBeFound) {
            if (printDebugData) {
                cout << "Number of comparisons: " << comparisons << endl;
            }
            return true;
        }

        if (aSortedVector[mid] < itemToBeFound) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }

        comparisons++;

        if (printDebugData && left <= right) {
            cout << "Comparing with element at index " << mid << endl;
        }
    }

    if (printDebugData) {
        cout << "Number of comparisons: " << comparisons << endl;
    }

    return false;
}

int main() {
    vector<int> sortedVector = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int key = 14;

    cout << "Size of the vector: " << sortedVector.size() << endl;

    bool found = binarySearch(sortedVector, key, true);

    if (found) {
        cout << "The item can be found in the vector." << endl;
    } else {
        cout << "The item cannot be found in the vector." << endl;
    }

    return 0;
}
