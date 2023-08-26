// William Romine
// 00103649
// Dr. Lewis CS372

#pragma once
#include <iostream>

template <typename T>
class vector {
public:
  vector() {
    arr = new T[1];
    vCapacity = 1;
    length = 0;
  }
  ~vector() {
    delete [] arr;
    arr = nullptr;
  }

  void put(T data, int index) {
    if (index == vCapacity) {
      push_back(data);
    }
    else {
      arr[index] = data;
    }
  }

  void push_back(T data) {
    // if number of elements is equal to capacity
        // than we need to reallocate and deep copy
        if (length == vCapacity) {
            expand(2 * vCapacity);
        }
        arr[length] = data;
        length++;
  }

  T &at(int index) {
    if (index < 0 || index > length) {
            std::cerr << "Vector: index out of bounds on access" << std::endl;
            exit(1);
        }
        else {
            return arr[index];
        }
  }

  int size() {
    return length;
  }

  int capacity() {
    return vCapacity;
  }

  void traverse() {
        for (int i = 0; i < length; i++) {
            std::cout << arr[i] << std::endl;
        }
        std::cout << std::endl;
  }

    bool operator==(vector& other) const {
        if (other.size() != length) {
            return false;
        }
        else {
            for (int i = 0; i < length; i++) {
                if (arr[i] != other.get(i)) {
                    return false;
                }
            }
        }
        return true;
    };

  T& operator[](int i) {
    if ((i < 0) || (i >= length)) {
      std::cerr << std::endl << "Vector index out of bounds" << std::endl;
    }
    return at(i);
  }

    vector& operator=(const vector& source) {
        // Do a self check.
        if (this == &source)
        {
            return *this;
        }
        // Reset self
        delete[] arr;
        arr = new T[1];
        vCapacity = 1;
        length = 1;
        for (int i = 0; i < source.size(); i++) {
            push_back(source.at(i));
        }
        return *this;
    }
private:
  T *arr = new T[1];
  int vCapacity = 1;
  int length = 1;

  void expand(int newCapacity) {
    if (newCapacity > vCapacity) {
      T *temp = new T[newCapacity];
      for (int i = 0; i < length; i++) {
        temp[i] = arr[i];
      }
      delete[] arr;
      vCapacity = newCapacity;
      arr = temp;
    }
    else {
      std::cerr << "vector::expand: new capacity is less than equal to current\n";
    }
  }
};
