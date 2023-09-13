// William Romine
// 00103649
// Dr. Lewis CS372

#pragma once
#include <cstddef>
#include "seqcontainer.h"

//Used some ideas of code from https://stackoverflow.com/questions/6902565/template-container-with-contained-class-definition-that-only-needs-one-of-multip/6902614#6902614

template <typename T, size_t Size>
class Array : public SeqContainer<T> {
public:
    Array(const T& initialValue) : SeqContainer<T>() {
        for (size_t i = 0; i < Size; ++i) {
            this->insert(this->end(), initialValue);
        }
    }

    Array(const Array& other) {
        for (size_t i = 0; i < Size; ++i) {
            elements[i] = other.data[i];
        }
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            for (size_t i = 0; i < Size; ++i) {
                elements[i] = other.data[i];
            }
        }
        return *this;
    }

    T& operator[](size_t index) {
        return elements[index];
    }

    const T& operator[](size_t index) const {
        return elements[index];
    }

    size_t size() const {
        return Size;
    }

private:
    T elements[Size];
};

#include <iostream>

int main() {
    Array<double, 3> doubleArray(2.45);
    
    doubleArray[0] = 4.45;
    doubleArray[1] = 8.45;
    doubleArray[2] = 16.45;

    for (size_t i = 0; i < doubleArray.size(); ++i) {
        std::cout << doubleArray[i] << " " << std::endl;
    }

    return 0;
}
