#pragma once
#include <functional>

template <typename T>
class List {
private:
    class Node {
    public:
        T data;
        Node* prev;
        Node* next;
        bool isHiddenNode = false;

        Node() : prev(nullptr), next(nullptr), isHiddenNode(false) {}
        Node(const T& value, Node* p = nullptr, Node* n = nullptr) : data(value), prev(p), next(n), isHiddenNode(false) {}
    };

    Node* head;
    Node* tail;

public:
    class const_iterator {
    protected:
        Node* current;

        T& retrieve() const {
            return current->data;
        }

        const_iterator(Node* p) : current(p) {}

        friend class List<T>;

    public:
        const_iterator() : current(nullptr) {}

        T& operator*() const {
            return retrieve();
        }

        const_iterator& operator++() {
            current = current->next;
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator old = *this;
            ++(*this);
            return old;
        }

        bool operator==(const const_iterator& rhs) const {
            return current == rhs.current;
        }

        bool operator!=(const const_iterator& rhs) const {
            return !(*this == rhs);
        }
    };

public:
    class iterator : public const_iterator {
    protected:
        iterator(Node* p) : const_iterator(p) {}

        friend class List<T>;

    public:
        iterator() {}

        T& operator*() {
            return const_iterator::retrieve();
        }

        const T& operator*() const {
            return const_iterator::operator*();
        }

        iterator& operator++() {
            this->current = const_iterator::current->next;
            return *this;
        }

        iterator operator++(int) {
            iterator old = *this;
            ++(*this);
            return old;
        }
    };

private:
    void setupList() {
        Node* newNode = new Node();
        newNode->next = tail;
        newNode->prev = head;
        head->next = newNode;
        tail->prev = newNode;
    }

    void deleteListContents() {
        Node* current = head->next;
        Node* temp = nullptr;
        while (current != tail->prev) {
            temp = current->next;
            delete current;
            current = temp;
        }
    }

public:
    List() {
        head = new Node();
        head->isHiddenNode = true;
        tail = new Node();
        tail->isHiddenNode = true;
        head->prev = nullptr;
        head->next = tail;
        tail->prev = head;
        tail->next = nullptr;
    }

    List(const T& newData) {
        setupList();
        (head->next)->data = newData;
    }

    List(const List& rhs) {
        head = new Node();
        tail = new Node();
        head->prev = nullptr;
        head->next = tail;
        tail->prev = head;
        tail->next = nullptr;

        for (auto it = rhs.cbegin(); it != rhs.cend(); ++it) {
            push_back(*it);
        }
    }

    ~List() {
        deleteListContents();
        delete head;
        delete tail;
    }

    bool empty() const {
        return (head->next == tail);
    }

    iterator begin() {
        return {head->next};
    }

    iterator end() {
        return tail;
    }

    const_iterator cbegin() const {
        return {head->next};
    }

    const_iterator cend() const {
        return tail;
    }

    iterator erase(iterator itr) {
        Node* p = itr.current;
        iterator iterToReturn{p->next};
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        return iterToReturn;
    }

    iterator insert(iterator itr, const T& x) {
        Node* p = itr.current;
        Node* newNode = new Node{x, p->prev, p};
        p->prev = p->prev->next = newNode;
        return {newNode};
    }

    iterator erase(iterator from, iterator to) {
        iterator itr = from;
        while (itr != to) {
            itr = erase(itr);
        }
        return to;
    }

    void push_front(const T& data) {
        Node* actualHead = head->next;
        Node* newNode = new Node(data, head, actualHead);
        actualHead->prev = newNode;
        head->next = newNode;
    }

    void push_back(const T& data) {
        Node* actualTail = tail->prev;
        Node* newNode = new Node(data, actualTail, tail);
        actualTail->next = newNode;
        tail->prev = newNode;
    }

    T front() const {
        return (head->next->data);
    }

    T back() const {
        return (tail->prev->data);
    }

    void pop_back() {
        if (!empty()) {
            Node* lastNode = tail->prev;
            tail->prev = lastNode->prev;
            Node* newLastNode = tail->prev;
            newLastNode->next = tail;
            delete lastNode;
        } else {
            std::cerr << "pop_back(): Attempt to pop from empty list. " << std::endl;
        }
    }

    void pop_front() {
        if (!empty()) {
            Node* firstNode = head->next;
            head->next = firstNode->next;
            Node* newFirstNode = head->next;
            newFirstNode->prev = head;
            delete firstNode;
        } else {
            std::cerr << "pop_front(): Attempt to pop from empty list. " << std::endl;
        }
    }

    void traverse(std::function<void(T& data)> doIt) {
        Node* current = head->next;
        while (current != tail) {
            doIt(current->data);
            current = current->next;
        }
    }
};

