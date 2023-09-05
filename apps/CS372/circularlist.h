#pragma once
#include <iostream>
#include "list.h"

template <typename T>
class CircularList : public List<T> {
public:
    using List<T>::Node;
    using typename List<T>::const_iterator;
    using typename List<T>::iterator;

    CircularList() : List<T>() {
        this->head->prev = this->tail;
        this->tail->next = this->head;
    }

    void circle(const_iterator start) {
        const_iterator current = start;
        do {
            std::cout << *current << " ";
            ++current;
            if (current == this->cend()) {
                current = this->cbegin();
            }
        } while (current != start);
        std::cout << std::endl;
    }
};

