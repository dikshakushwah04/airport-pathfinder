#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Graph.h"
#include <vector>
#include <unordered_map>

struct PathResult {
    std::vector<int> path;
    double totalDistance;
    bool pathFound;
    
    PathResult() : totalDistance(0.0), pathFound(false) {}
};

class Dijkstra {
private:
    const Graph& graph;
    
public:
    explicit Dijkstra(const Graph& g);
    
    PathResult findShortestPath(int sourceId, int destinationId);
    
    std::vector<int> reconstructPath(
        const std::unordered_map<int, int>& previous,
        int sourceId,
        int destinationId
    );
};

#endif