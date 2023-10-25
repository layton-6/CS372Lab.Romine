// William Romine
// 00103649
// Dr. Lewis CS372

// Helpful article in understanding the adjlist and social graphs in c++ for this problem. https://medium.com/@elifsenaa13/graph-data-structure-code-with-c-7865521849c3

#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <unordered_map>

class SocialGraph {
public:
    // Constructor to initialize the social graph with 20 people
    SocialGraph() : numPeople(20) {
        // Initialize adjacency list with 20 people
        adjList.resize(numPeople);
    }
    // Function to add a connection between two people
    void addCnt(int person1, int person2) {
        if (person1 < numPeople && person2 < numPeople) {
            adjList[person1].push_back(person2);
            adjList[person2].push_back(person1);
        }
    }
    // Function to check if there is a path from "you" to "Kevin Bacon"
    bool cntKBacon(int you, std::vector<int>& path) {
        if (you < 0 || you >= numPeople) {
            return false;
        }
        std::queue<int> q;
        std::vector<bool> visited(numPeople, false);
        std::unordered_map<int, int> parent;
        q.push(you);
        visited[you] = true;
        parent[you] = -1;
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            if (current == kevBacon) {
                // Reconstruct the path from Kevin Bacon to you
                int node = kevBacon;
                while (node != -1) {
                    path.insert(path.begin(), node);
                    node = parent[node];
                }
                return true;
            }
            for (int neighbor : adjList[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    parent[neighbor] = current;
                    q.push(neighbor);
                }
            }
        }
        // No path from you to Kevin Bacon
        return false;
    }
private:
    // Assuming Kevin Bacon is at index 0
    const int kevBacon = 0;
    int numPeople;
    std::vector<std::list<int>> adjList;
};

int main() {
    SocialGraph socialGraph;
    socialGraph.addCnt(0, 1);  // Connect Kevin Bacon to someone
    socialGraph.addCnt(1, 2);  // Connect someone to someone else
    int you = 2;
    std::vector<int> path;
    bool connected = socialGraph.cntKBacon(you, path);

    if (connected) {
        std::cout << "You are indeed connected to Kevin Bacon!" << std::endl;
        std::cout << "Path: ";
        for (int person : path) {
            std::cout << person << " -> ";
        }
        std::cout << "Kevin Bacon" << std::endl;
    } else {
        std::cout << "You are not connected to Kevin Bacon." << std::endl;
    }

    return 0;
}

