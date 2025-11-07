#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include "Graph.h"
#include "Dijkstra.h"

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n\"");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n\"");
    return str.substr(first, last - first + 1);
}

std::vector<std::string> parseCSVLine(const std::string& line) {
    std::vector<std::string> fields;
    std::string field;
    bool inQuotes = false;
    
    for (char c : line) {
        if (c == '"') {
            inQuotes = !inQuotes;
        } else if (c == ',' && !inQuotes) {
            fields.push_back(trim(field));
            field.clear();
        } else {
            field += c;
        }
    }
    fields.push_back(trim(field));
    return fields;
}

bool loadAirports(Graph& graph, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filename << std::endl;
        return false;
    }
    
    std::string line;
    int count = 0;
    
    while (std::getline(file, line)) {
        auto fields = parseCSVLine(line);
        
        if (fields.size() >= 8) {
            try {
                Airport airport;
                airport.id = std::stoi(fields[0]);
                airport.name = fields[1];
                airport.city = fields[2];
                airport.country = fields[3];
                airport.iata = fields[4];
                airport.latitude = std::stod(fields[6]);
                airport.longitude = std::stod(fields[7]);
                
                if (!airport.iata.empty() && airport.iata != "\\N") {
                    graph.addAirport(airport);
                    count++;
                }
            } catch (const std::exception& e) {
                continue;
            }
        }
    }
    
    file.close();
    std::cout << "Loaded " << count << " airports." << std::endl;
    return count > 0;
}

void displayPath(const Graph& graph, const PathResult& result) {
    if (!result.pathFound) {
        std::cout << "\n❌ No path found between these airports!" << std::endl;
        return;
    }
    
    std::cout << "\n✈️  SHORTEST PATH FOUND!\n";
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
    std::cout << "Total Distance: " << std::fixed << std::setprecision(2) 
              << result.totalDistance << " km\n";
    std::cout << "Number of Stops: " << (result.path.size() - 1) << "\n\n";
    std::cout << "Route:\n";
    
    for (size_t i = 0; i < result.path.size(); i++) {
        Airport airport = graph.getAirport(result.path[i]);
        std::cout << (i + 1) << ". " << airport.iata << " - " 
                  << airport.name << " (" << airport.city << ", " 
                  << airport.country << ")\n";
        
        if (i < result.path.size() - 1) {
            Airport nextAirport = graph.getAirport(result.path[i + 1]);
            double segmentDist = graph.calculateDistance(
                airport.latitude, airport.longitude,
                nextAirport.latitude, nextAirport.longitude
            );
            std::cout << "   ↓ " << std::fixed << std::setprecision(2) 
                      << segmentDist << " km\n";
        }
    }
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
}

void searchAirportByCode(const Graph& graph, const std::string& code) {
    for (const auto& pair : graph.getAllAirports()) {
        if (pair.second.iata == code) {
            const Airport& a = pair.second;
            std::cout << "\n✓ Found: " << a.iata << " - " << a.name 
                      << " (" << a.city << ", " << a.country << ")\n";
            return;
        }
    }
    std::cout << "\n✗ Airport code not found: " << code << "\n";
}

int getAirportIdByCode(const Graph& graph, const std::string& code) {
    for (const auto& pair : graph.getAllAirports()) {
        if (pair.second.iata == code) {
            return pair.first;
        }
    }
    return -1;
}

int main() {
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
    std::cout << "        GLOBAL AIRPORT SHORTEST PATH FINDER\n";
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n";
    
    Graph graph;
    
    std::cout << "Loading airport data...\n";
    if (!loadAirports(graph, "data/airports.dat")) {
        std::cerr << "Failed to load airports. Make sure data/airports.dat exists!\n";
        return 1;
    }
    
    std::cout << "Building connections between airports...\n";
    graph.buildConnections();
    
    std::cout << "\n📊 Graph Statistics:\n";
    std::cout << "   Airports: " << graph.getAirportCount() << "\n";
    std::cout << "   Connections: " << graph.getEdgeCount() << "\n\n";
    
    while (true) {
        std::cout << "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
        std::cout << "MENU:\n";
        std::cout << "1. Find shortest path between two airports\n";
        std::cout << "2. Search airport by code\n";
        std::cout << "3. Exit\n";
        std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
        std::cout << "Enter choice: ";
        
        std::string choiceStr;
        std::getline(std::cin, choiceStr);
        
        if (choiceStr.empty()) continue;
        
        int choice;
        try {
            choice = std::stoi(choiceStr);
        } catch (...) {
            std::cout << "\n❌ Invalid choice. Please try again.\n";
            continue;
        }
        
        if (choice == 1) {
            std::string sourceCode, destCode;
            std::cout << "\nEnter source airport code (e.g., LAX): ";
            std::cin >> sourceCode;
            std::cout << "Enter destination airport code (e.g., JFK): ";
            std::cin >> destCode;
            
            int sourceId = getAirportIdByCode(graph, sourceCode);
            int destId = getAirportIdByCode(graph, destCode);
            
            if (sourceId == -1 || destId == -1) {
                std::cout << "\n❌ One or both airport codes not found!\n";
                continue;
            }
            
            std::cout << "\nCalculating shortest path...\n";
            Dijkstra dijkstra(graph);
            PathResult result = dijkstra.findShortestPath(sourceId, destId);
            displayPath(graph, result);
            
        } else if (choice == 2) {
            std::string code;
            std::cout << "\nEnter airport code: ";
            std::cin >> code;
            searchAirportByCode(graph, code);
            
        } else if (choice == 3) {
            std::cout << "\n✈️  Thank you for using Airport Pathfinder!\n";
            break;
        } else {
            std::cout << "\n❌ Invalid choice. Please try again.\n";
        }
    }
    
    return 0;
}