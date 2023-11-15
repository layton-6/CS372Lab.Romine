// William Romine
// 00103649
// Dr. Lewis CS372

// Used geekforgeeks to help format and understand quadratic probing https://www.geeksforgeeks.org/quadratic-probing-in-hashing/

#include <cstddef>
#include <cassert>
#include <iostream>

template <class RecordType>
class Table {
public:
    static const std::size_t CAPACITY = 811;
    Table();
    void insert(const RecordType &entry);
    void remove(int key);
    bool isPresent(int key) const;
    void find(int key, bool &found, RecordType &result) const;
    std::size_t size() const;

private:
    static const int NEVERUSED = -1;
    static const int PREVIOUSLYUSED = -2;
    RecordType data[CAPACITY];
    std::size_t used;

    std::size_t hash(int key) const;
    std::size_t nextIndex(std::size_t index) const;
    std::size_t quadProbe(std::size_t index) const;

    void findIndex(int key, bool &found, std::size_t &index) const {
        std::size_t count = 0;
        index = hash(key);
        while ((count < CAPACITY) && (!neverUsed(index)) && (data[index].key != key)) {
            ++count;
            index = quadProbe(index);
        }
        found = (data[index].key == key);
    }

    bool neverUsed(std::size_t index) const { return (index == NEVERUSED); }
    bool isVacant(std::size_t index) const { return (index == PREVIOUSLYUSED); }
};

template <class RecordType>
Table<RecordType>::Table() : used(0) {}

template <class RecordType>
void Table<RecordType>::insert(const RecordType &entry) {
    bool alreadyPresent;
    std::size_t index;
    assert(entry.key >= 0);
    findIndex(entry.key, alreadyPresent, index);
    if (!alreadyPresent) {
        assert(size() < CAPACITY);
        index = hash(entry.key);
        while (!isVacant(index)) {
            index = quadProbe(index);
        }
        ++used;
    }
    data[index] = entry;
}

template <class RecordType>
void Table<RecordType>::remove(int key) {
    bool found;
    std::size_t index;
    assert(key >= 0);
    findIndex(key, found, index);
    if (found) {
        data[index].key = PREVIOUSLYUSED;
        --used;
    }
}

template <class RecordType>
bool Table<RecordType>::isPresent(int key) const {
    bool found;
    std::size_t index;
    findIndex(key, found, index);
    return found;
}

template <class RecordType>
void Table<RecordType>::find(int key, bool &found, RecordType &result) const {
    std::size_t index;
    findIndex(key, found, index);
    if (found) {
        result = data[index];
    }
}

template <class RecordType>
std::size_t Table<RecordType>::size() const {
    return used;
}

template <class RecordType>
std::size_t Table<RecordType>::hash(int key) const {
    return key % CAPACITY;
}

template <class RecordType>
std::size_t Table<RecordType>::nextIndex(std::size_t index) const {
    return (index + 1) % CAPACITY;
}

template <class RecordType>
std::size_t Table<RecordType>::quadProbe(std::size_t index) const {
    // Quadratic probing: 1^2, 2^2, 3^2, ...
    return (index + ((index + 1) / 2) * ((index + 1) / 2)) % CAPACITY;
}

struct Record {
    int key;
};

int main() {
    // For Example
    Table<Record> myTable;

    Record record1{42};
    Record record2{17};
    Record record3{99};

    myTable.insert(record1);
    myTable.insert(record2);
    myTable.insert(record3);

    std::cout << "Size of the table: " << myTable.size() << std::endl;

    bool found;
    Record result;
    int searchKey = 17;
    myTable.find(searchKey, found, result);

    if (found) {
        std::cout << "Record with key " << searchKey << " found." << std::endl;
    } else {
        std::cout << "Record with key " << searchKey << " not found." << std::endl;
    }

    int removeKey = 42;
    myTable.remove(removeKey);
    std::cout << "Size of the table after removing a record: " << myTable.size() << std::endl;

    return 0;
}
