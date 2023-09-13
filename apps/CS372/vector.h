// William Romine
// 00103649
// Dr. Lewis CS372

#pragma once
#include <iostream>
#include "seqcontainer.h"

//Used some ideas of code from for my vector and array classes https://stackoverflow.com/questions/6902565/template-container-with-contained-class-definition-that-only-needs-one-of-multip/6902614#6902614

template <typename T>
class Vector : public SeqContainer<T> {
public:
    Vector() : SeqContainer<T>() {}

    void put(T data, int index) {
        if (index == this->size()) {
            this->push_back(data);
        }
        else {
            auto it = this->begin();
            for (int i = 0; i < index; ++i) {
                ++it;
            }
            this->insert(it, data);
        }
    }

    T& at(int index) {
        if (index < 0 || index >= this->size()) {
            std::cerr << "Index out of bounds for Vector." << std::endl;
            exit(1);
        }
        else {
            auto it = this->begin();
            for (int i = 0; i < index; ++i) {
                ++it;
            }
            return *it;
        }
    }

    int size() {
        return this->size();
    }

    void traverse() {
        auto it = this->begin();
        while (it != this->end()) {
            std::cout << *it << std::endl;
            ++it;
        }
        std::cout << std::endl;
    }

};
