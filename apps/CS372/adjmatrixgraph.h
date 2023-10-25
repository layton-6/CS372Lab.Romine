#include <vector>
#include <iostream>
#include <cstddef>

template <class N>
class Graph {
public:
    Graph() {}
    Graph(std::vector<N> nodes, std::vector<std::pair<N, N>> edges) {}
    virtual ~Graph() {}
    virtual bool adjacent(N x, N y) = 0;
    virtual std::vector<N> neighbors(N x) = 0;
    virtual void addNode(N x) = 0;
    virtual void addEdge(N x, N y) = 0;
    virtual void deleteEdge(N x, N y) = 0;
};
template <class N>
class AdjMatrixGraph : public Graph<N> {
private:
    static const int MaxSize = 100;
    std::vector<N> nodeVector;
    std::byte adjMatrix[MaxSize][MaxSize];
    unsigned int numNodes = 0;
public:
    AdjMatrixGraph() : Graph<N>() {}
    AdjMatrixGraph(const AdjMatrixGraph& other) : Graph<N>() , nodeVector(other.nodeVector), edgesVector(other.edgesVector) { }
    AdjMatrixGraph& operator=(const AdjMatrixGraph& source) {
        if (this == &source) {
            return *this; // Handle self-assignment
        }
        nodeVector = source.nodeVector;
        edgesVector = source.edgesVector;
        return *this;
    }
    AdjMatrixGraph(std::vector<N> newNodes, std::vector<std::pair<N, N>> newEdges)
        : Graph<N>(newNodes, newEdges) {
        for (const N& node : newNodes) {
            addNode(node);
        }
        for (const auto& edge : newEdges) {
            addEdge(edge.first, edge.second);
        }
    }
    ~AdjListGraph() { }
    // Implement from base class
    virtual bool adjacent(N x, N y) {
        // Implement the logic to check if nodes 'x' and 'y' are adjacent
        if (x < nodeVector.size() && y < nodeVector.size()) {
            const Edges& neighbors = edgesVector[x];
            return std::find(neighbors.begin(), neighbors.end(), y) != neighbors.end();
        }
        return false;
    }
    virtual std::vector<N> neighbors(N x) {
        if (x < nodeVector.size()) {
            const Edges& neighbors = edgesVector[x];
            return std::vector<N>(neighbors.begin(), neighbors.end());
        }
        return std::vector<N>();
    }
    virtual void addNode(N node) {
        if (std::find(nodeVector.begin(), nodeVector.end(), node) == nodeVector.end()) {
            nodeVector.push_back(node);
            edgesVector.push_back(Edges());
        }
    }
    virtual void addEdge(N x, N y) {
        if (x < nodeVector.size() && y < nodeVector.size()) {
            edgesVector[x].push_back(y);
        }
    }
    virtual void deleteEdge(N x, N y) {
        if (x < nodeVector.size() && y < nodeVector.size()) {
            Edges& neighbors = edgesVector[x];
            neighbors.remove(y);
        }
    }
};

