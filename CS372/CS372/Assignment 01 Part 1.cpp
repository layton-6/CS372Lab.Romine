// William Romine
// 00103649
// Dr. Lewis CS372

#include <iostream>
#include <string>

void demoArrayDelete() {
    const int arraySize = 1000000;
    int* ptr1 = new int[arraySize];
    for (int i = 0; i < arraySize; ++i) {
        ptr1[i] = i;
    }

    int* ptr2 = ptr1;
    delete[] ptr1;

    for (int i = 0; i < 10; ++i) {
        std::cout << ptr2[i] << " ";
    }
    std::cout << std::endl;
}

void demoMemoryLeak() {
    const int arraySize = 1000000;
    int* ptr1 = new int[arraySize];
    for (int i = 0; i < arraySize; ++i) {
        ptr1[i] = i;
    }

    int* ptr2 = ptr1;

    delete[] ptr1;

    std::cout << "Pointer 2 address: " << ptr2 << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << ptr2[i] << " ";
    }
    std::cout << std::endl;
}

std::string* createStringOnHeap() {
    std::string* strPtr = new std::string("abcdefghijkl");
    return strPtr;
}

void demoStringMemoryLeak() {
    std::string* strPtr = createStringOnHeap();
    std::cout << "String: " << *strPtr << std::endl;
    delete strPtr;  // Deleting the string pointer, but the string content has been leaked
}

int main() {
    std::cout << "Demo 1: Array Delete" << std::endl;
    demoArrayDelete();

    std::cout << "\nDemo 2: Memory Leak" << std::endl;
    demoMemoryLeak();

    std::cout << "\nDemo 3: String Memory Leak" << std::endl;
    demoStringMemoryLeak();

    return 0;
}

