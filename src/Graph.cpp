#include "Graph.h"
#include <cmath>
#include <algorithm>

void Graph::addAirport(const Airport& airport) {
    airports[airport.id] = airport;
}

void Graph::addEdge(int source, int destination, double weight) {
    adjacencyList[source].push_back(Edge(destination, weight));
}

bool Graph::hasAirport(int id) const {
    return airports.find(id) != airports.end();
}

Airport Graph::getAirport(int id) const {
    return airports.at(id);
}

const std::vector<Edge>& Graph::getNeighbors(int id) const {
    static std::vector<Edge> empty;
    auto it = adjacencyList.find(id);
    if (it != adjacencyList.end()) {
        return it->second;
    }
    return empty;
}

const std::unordered_map<int, Airport>& Graph::getAllAirports() const {
    return airports;
}

int Graph::getAirportCount() const {
    return airports.size();
}

int Graph::getEdgeCount() const {
    int count = 0;
    for (const auto& pair : adjacencyList) {
        count += pair.second.size();
    }
    return count;
}

double Graph::calculateDistance(double lat1, double lon1, double lat2, double lon2) const {
    const double R = 6371.0;
    
    double lat1Rad = lat1 * M_PI / 180.0;
    double lat2Rad = lat2 * M_PI / 180.0;
    double deltaLat = (lat2 - lat1) * M_PI / 180.0;
    double deltaLon = (lon2 - lon1) * M_PI / 180.0;
    
    double a = sin(deltaLat / 2) * sin(deltaLat / 2) +
               cos(lat1Rad) * cos(lat2Rad) *
               sin(deltaLon / 2) * sin(deltaLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    
    return R * c;
}

void Graph::buildConnections() {
    std::vector<std::pair<int, Airport>> airportList;
    for (const auto& pair : airports) {
        airportList.push_back(pair);
    }
    
    const int MAX_CONNECTIONS = 50;
    const double MAX_DISTANCE = 2000.0;
    
    for (size_t i = 0; i < airportList.size(); i++) {
        std::vector<std::pair<double, int>> distances;
        
        for (size_t j = 0; j < airportList.size(); j++) {
            if (i != j) {
                double dist = calculateDistance(
                    airportList[i].second.latitude,
                    airportList[i].second.longitude,
                    airportList[j].second.latitude,
                    airportList[j].second.longitude
                );
                
                if (dist <= MAX_DISTANCE) {
                    distances.push_back({dist, airportList[j].first});
                }
            }
        }
        
        std::sort(distances.begin(), distances.end());
        
        int connectionsAdded = 0;
        for (const auto& pair : distances) {
            if (connectionsAdded >= MAX_CONNECTIONS) break;
            addEdge(airportList[i].first, pair.second, pair.first);
            connectionsAdded++;
        }
    }
}