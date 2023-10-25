template <class N>
class AdjListGraph : public Graph<N> {
private:
    using Edges = std::list<N>;
    std::vector<N> nodeVector;
    std::vector<Edges> edgesVector;
public:
    // Default constructor, create an empty graph
    AdjListGraph() : Graph<N>() { }
    AdjListGraph(const AdjListGraph& other) : Graph<N>(), nodeVector(other.nodeVector), edgesVector(other.edgesVector) { }
    AdjListGraph& operator=(const AdjListGraph& source) {
        if (this == &source) {
            return *this; // Handle self-assignment
            }
        nodeVector = source.nodeVector;
        edgesVector = source.edgesVector;
        return *this;
    }
    AdjListGraph(std::vector<N> newNodes, std::vector<std::pair<N, N>> newEdges)
        : Graph<N>(newNodes, newEdges) {
        for (const N& node : newNodes) {
            addNode(node);
        }
        for (const auto& edge : newEdges) {
            addEdge(edge.first, edge.second);
        }
    }
    // Destructor
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

