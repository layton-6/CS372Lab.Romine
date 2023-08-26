// William Romine
// 00103649
// Dr. Lewis CS372

#include <cstddef>

template <typename T, size_t Size>
class Array {
public:
    Array() = default;
    explicit Array(const T& initialValue) {
        for (size_t i = 0; i < Size; ++i) {
            data[i] = initialValue;
        }
    }

    Array(const Array& other) {
        for (size_t i = 0; i < Size; ++i) {
            data[i] = other.data[i];
        }
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            for (size_t i = 0; i < Size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    T& operator[](size_t index) {
        return data[index];
    }

    const T& operator[](size_t index) const {
        return data[index];
    }

    size_t size() const {
        return Size;
    }

private:
    T data[Size];
};

#include <iostream>

int main() {
    Array<int, 5> intArray;
    intArray[0] = 10;
    intArray[1] = 20;
    intArray[2] = 30;
    intArray[3] = 40;
    intArray[4] = 50;

    for (size_t i = 0; i < intArray.size(); ++i) {
        std::cout << intArray[i] << " ";
    }

    return 0;
}
