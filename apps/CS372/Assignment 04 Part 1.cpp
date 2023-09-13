// William Romine
// 00103649
// Dr. Lewis CS372

#include <iostream>
#include "list.h" //Using the list.h we've worked to create.

using namespace std;

class cirLinkedList {
private:
    List<int> circleOfPeople;
    int size;

public:
    cirLinkedList() : size(0) {}

    void insert(int val) {
        circleOfPeople.push_back(val);
        size++;
    }

    int eliminate(int M) {
        auto it = circleOfPeople.begin();
        while (size > 1) {
            for (int i = 0; i < M - 1; ++i) {
                ++it;
                if (it == circleOfPeople.end()) {
                    it = circleOfPeople.begin();
                }
            }
            it = circleOfPeople.erase(it);
            if (it == circleOfPeople.end()) {
                it = circleOfPeople.begin();
            }
            size--;
            
        }
        return circleOfPeople.front();
    }
};

int main() {
    int N, M;
    cout << "Total number of people (N): ";
    cin >> N;
    cout << "Number of passes for the Hot Potato (M): ";
    cin >> M;
    
    cirLinkedList circle;
    
    for (int i = 1; i <= N; ++i) {
        circle.insert(i);
    }
    
    int winner = circle.eliminate(M);
    
    cout << "Winner: " << winner << endl;
    
    return 0;
}
