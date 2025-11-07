#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

struct Airport {
    int id;
    std::string name;
    std::string city;
    std::string country;
    std::string iata;
    double latitude;
    double longitude;
};

struct Edge {
    int destinationId;
    double weight;
    
    Edge(int dest, double w) : destinationId(dest), weight(w) {}
};

class Graph {
private:
    std::unordered_map<int, Airport> airports;
    std::unordered_map<int, std::vector<Edge>> adjacencyList;
    
public:
    void addAirport(const Airport& airport);
    void addEdge(int source, int destination, double weight);
    
    bool hasAirport(int id) const;
    Airport getAirport(int id) const;
    const std::vector<Edge>& getNeighbors(int id) const;
    const std::unordered_map<int, Airport>& getAllAirports() const;
    
    int getAirportCount() const;
    int getEdgeCount() const;
    
    double calculateDistance(double lat1, double lon1, double lat2, double lon2) const;
    
    void buildConnections();
};

#endif