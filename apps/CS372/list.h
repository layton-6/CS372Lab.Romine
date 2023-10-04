#pragma once
#include <functional>
#include <memory>
#include "seqcontainer.h"

template <typename T>
class List : public SeqContainer<T> {
public:
    using typename SeqContainer<T>::Node;
    using SeqContainer<T>::head;
    using SeqContainer<T>::tail;
    using SeqContainer<T>::setupList;

    List() = default;
    List(T newData) : SeqContainer<T>(newData) {}
    List(const List& rhs) : SeqContainer<T>(rhs) {}
    ~List() = default;

    bool empty() const {
        return (head->next == tail);
    }

    void push_front(T data) {
        if (this->empty()) {
            setupList();
            auto actualHead = head->next;
            actualHead->data = data;
        } else {
            auto actualHead = head->next;
            auto newNode = std::shared_ptr<Node>(); //New Shared Pointer from Lecture
            newNode->data = data;
            newNode->next = actualHead;
            actualHead->prev = newNode.get(); //Had to use .get() to pull from shared pointer
            newNode->prev = head;
            head->next = newNode.get(); //Had to use .get() to pull from shared pointer
        }
    }

    void push_back(T data) {
        if (this->empty()) {
            setupList();
            auto actualTail = tail->prev;
            actualTail->data = data;
        } else {
            auto actualTail = tail->prev;
            auto newNode = std::shared_ptr<Node>(); //New Shared Pointer from Lecture
            newNode->data = data;
            newNode->prev = actualTail;
            actualTail->next = newNode.get(); //Had to use .get() to pull from shared pointer
            newNode->next = tail;
            tail->prev = newNode.get(); //Had to use .get() to pull from shared pointer
        }
    }

    T front() {
        auto actualHead = head->next;
        return (actualHead->data);
    }

    T back() {
        auto actualTail = tail->prev;
        return (actualTail->data);
    }

    void pop_back() {
        if (!empty()) {
            auto lastNode = tail->prev;
            tail->prev = lastNode->prev;
            auto newLastNode = tail->prev;
            newLastNode->next = tail;
        } else {
            std::cerr << "pop_back(): Attempt to pop from an empty list." << std::endl;
        }
    }

    void pop_front() {
        if (!empty()) {
            auto firstNode = head->next;
            head->next = firstNode->next;
            auto newFirstNode = head->next;
            newFirstNode->prev = head;
        } else {
            std::cerr << "pop_front(): Attempt to pop from an empty list." << std::endl;
        }
    }

    void traverse(std::function<void(T& data)> doIt) {
        auto current = head->next;
        while (current != tail) {
            doIt(current->data);
            current = current->next;
        }
    }
};
