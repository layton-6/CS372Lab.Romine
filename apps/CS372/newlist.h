#pragma once
template <typename T>
class List
{
private:
    class Node {
    public:
        T  data;
        Node* prev;
        Node* next;
    };
    Node* head = nullptr;
    Node* tail = nullptr;
    void setupList() {
        Node* newNode = new Node();
        newNode->next = nullptr;
        newNode->prev = nullptr;
        head = newNode;
        tail = newNode;
    }
    void deleteListContents() {
        Node* current = head;
        Node* temp = nullptr;
        while (current != nullptr) {
            temp = current->next;
            delete current;
            current = temp;
        }
    }
public:
    List() = default;
    List(T newData) {
        setupList();
        head->data = newData;
    }
    List(List& rhs) { // copy constructor
        deleteListContents();
        head = rhs.head;
        tail = rhs.tail;
    }
    ~List() {// And a destructor
        deleteListContents();
    }
    bool  empty() {
        return (head == nullptr);
    }
    void push_front(T data)
    {
        if (this->empty()) {
            setupList();
            head->data = data;
            tail = head;
        }
        else {
            Node* newNode = new Node();
            newNode->data = data;
            newNode->next = head;
            newNode->prev = nullptr;
            head = newNode;
        }
    }
    void push_back(T data)
    {
        if (this->empty()) {
            setupList();
            head->data = data;
            tail = head;
        }
        else {
            Node* newNode = new Node();
            newNode->data = data;
            newNode->next = nullptr;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    T front() {
        return (head->data);
    }
    T back() {
        return (tail->data);
    }
    void pop_back() {
        Node* lastNode = tail;
        tail = tail.prev;
        tail.next = nullptr;
        delete lastNode;
    }
    void pop_front() {
        Node* firstNode = head;
        head = head.next;
        head.prev = nullptr;
        delete firstNode;
    }
    void traverse(void (*doIt)(T data)) {
        Node* current = head;
        while (current != nullptr) {
            doIt(current->data);
            current = current->next;
        }
    }
};
