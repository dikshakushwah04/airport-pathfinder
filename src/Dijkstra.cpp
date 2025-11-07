#include "Dijkstra.h"
#include <queue>
#include <limits>
#include <algorithm>

Dijkstra::Dijkstra(const Graph& g) : graph(g) {}

PathResult Dijkstra::findShortestPath(int sourceId, int destinationId) {
    PathResult result;
    
    if (!graph.hasAirport(sourceId) || !graph.hasAirport(destinationId)) {
        return result;
    }
    
    std::unordered_map<int, double> distances;
    std::unordered_map<int, int> previous;
    std::unordered_map<int, bool> visited;
    
    using PQElement = std::pair<double, int>;
    std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> pq;
    
    for (const auto& pair : graph.getAllAirports()) {
        distances[pair.first] = std::numeric_limits<double>::infinity();
    }
    
    distances[sourceId] = 0.0;
    pq.push({0.0, sourceId});
    
    while (!pq.empty()) {
        int currentId = pq.top().second;
        double currentDist = pq.top().first;
        pq.pop();
        
        if (visited[currentId]) continue;
        visited[currentId] = true;
        
        if (currentId == destinationId) {
            break;
        }
        
        if (currentDist > distances[currentId]) continue;
        
        for (const Edge& edge : graph.getNeighbors(currentId)) {
            int neighborId = edge.destinationId;
            double newDist = distances[currentId] + edge.weight;
            
            if (newDist < distances[neighborId]) {
                distances[neighborId] = newDist;
                previous[neighborId] = currentId;
                pq.push({newDist, neighborId});
            }
        }
    }
    
    if (distances[destinationId] != std::numeric_limits<double>::infinity()) {
        result.pathFound = true;
        result.totalDistance = distances[destinationId];
        result.path = reconstructPath(previous, sourceId, destinationId);
    }
    
    return result;
}

std::vector<int> Dijkstra::reconstructPath(
    const std::unordered_map<int, int>& previous,
    int sourceId,
    int destinationId
) {
    std::vector<int> path;
    int current = destinationId;
    
    while (current != sourceId) {
        path.push_back(current);
        auto it = previous.find(current);
        if (it == previous.end()) {
            return std::vector<int>();
        }
        current = it->second;
    }
    path.push_back(sourceId);
    
    std::reverse(path.begin(), path.end());
    return path;
}
