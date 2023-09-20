#pragma once

template <typename T>
class SelfAdjustingList : public List<T>
{
public:
    SelfAdjustingList() = default;
    SelfAdjustingList(T newData) : List<T>(newData) {}

    T* find(T itemToFind)
    {
        Node* current = this->first;
        Node* previous = nullptr;

        while (current != nullptr)
        {
            if (current->data == itemToFind)
            {
                if (previous != nullptr)
                {
                    previous->next = current->next;
                    if (current == this->last)
                    {
                        this->last = previous;
                    }
                    current->next = this->first;
                    this->first->previous = current;
                    this->first = current;
                    current->previous = nullptr;
                }
                return &(this->first->data);
            }
            previous = current;
            current = current->next;
        }

        return nullptr;
    }
};


