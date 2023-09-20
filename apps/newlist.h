#pragma once

template <typename T>
class List
{
private:
    class Node {
    public:
        T value;
        Node* previous;
        Node* nextNode;
        bool isRemoved;
    };
    
    Node* headNode = nullptr;
    Node* tailNode = nullptr;
    int activeNodeCount = 0;
    int removedNodeCount = 0;

    void setupList() {
        Node* newNode = new Node();
        newNode->nextNode = nullptr;
        newNode->previous = nullptr;
        newNode->isRemoved = false;
        headNode = newNode;
        tailNode = newNode;
        activeNodeCount = 0;
        removedNodeCount = 0;
    }

    void clearListContents() {
        Node* currentNode = headNode;
        Node* tempNode = nullptr;
        while (currentNode != nullptr) {
            tempNode = currentNode->nextNode;
            delete currentNode;
            currentNode = tempNode;
        }
    }

public:
    List() = default;

    List(T newValue) {
        setupList();
        headNode->value = newValue;
        activeNodeCount = 1;
    }

    List(List& rhs) {
        clearListContents();
        headNode = rhs.headNode;
        tailNode = rhs.tailNode;
        activeNodeCount = rhs.activeNodeCount;
        removedNodeCount = rhs.removedNodeCount;
    }

    ~List() {
        clearListContents();
    }

    bool isEmpty() {
        return (activeNodeCount == 0);
    }

    void addToFront(T newValue) {
        if (isEmpty()) {
            setupList();
            headNode->value = newValue;
            tailNode = headNode;
            activeNodeCount = 1;
        }
        else {
            Node* newNode = new Node();
            newNode->value = newValue;
            newNode->nextNode = headNode;
            newNode->previous = nullptr;
            headNode->previous = newNode;
            headNode = newNode;
            activeNodeCount++;
        }
    }

    void addToBack(T newValue) {
        if (isEmpty()) {
            setupList();
            headNode->value = newValue;
            tailNode = headNode;
            activeNodeCount = 1;
        }
        else {
            Node* newNode = new Node();
            newNode->value = newValue;
            newNode->nextNode = nullptr;
            newNode->previous = tailNode;
            tailNode->nextNode = newNode;
            tailNode = newNode;
            activeNodeCount++;
        }
    }

    T getFront() {
        return (headNode->value);
    }

    T getBack() {
        return (tailNode->value);
    }

    void removeFromBack() {
        Node* lastNode = tailNode;
        tailNode = tailNode->previous;
        if (tailNode != nullptr) {
            tailNode->nextNode = nullptr;
        }
        delete lastNode;
        activeNodeCount--;
    }

    void removeFromFront() {
        Node* firstNode = headNode;
        headNode = headNode->nextNode;
        if (headNode != nullptr) {
            headNode->previous = nullptr;
        }
        delete firstNode;
        activeNodeCount--;
    }

    void forEach(void (*doSomething)(T value)) {
        Node* currentNode = headNode;
        while (currentNode != nullptr) {
            if (!currentNode->isRemoved) {
                doSomething(currentNode->value);
            }
            currentNode = currentNode->nextNode;
        }
    }

    void markRemoved(Node* node) {
        if (node && !node->isRemoved) {
            node->isRemoved = true;
            activeNodeCount--;
            removedNodeCount++;
        }
    }

    void removeMarkedNodes() {
        Node* current = headNode;
        while (current != nullptr) {
            Node* temp = current->nextNode;
            
            if (current->isRemoved) {
                if (current == headNode) {
                    headNode = current->nextNode;
                    if (headNode != nullptr) {
                        headNode->previous = nullptr;
                    }
                }
                else if (current == tailNode) {
                    tailNode = current->previous;
                    if (tailNode != nullptr) {
                        tailNode->nextNode = nullptr;
                    }
                }
                else {
                    current->previous->nextNode = current->nextNode;
                    current->nextNode->previous = current->previous;
                }
                
                delete current;
                removedNodeCount--;
            }
            
            current = temp;
        }
    }

    void checkDelete() {
        if (removedNodeCount == activeNodeCount) {
            deleteMarkedNodes();
        }
    }
};

