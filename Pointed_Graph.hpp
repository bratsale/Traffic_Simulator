#pragma once

#include <vector>
#include <unordered_map>
#include <fstream>
#include "Node.hpp"

class Pointed_Graph {
public:
    Pointed_Graph() = default;
    Pointed_Graph(const std::vector<Node*>& initial_nodes);

    void addNode(Node* node);
    void addPath(Path* path);

    const std::vector<Node*>& getNodes() const;
    const std::unordered_map<int, std::vector<Path*>>& getAdjList() const;

    void save(const std::string& filename) const;
    void load(const std::string& filename);

private:
    std::vector<Node*> nodes;
    std::unordered_map<int, std::vector<Path*>> adjList;
};
