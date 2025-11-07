Global Airport Shortest Path Finder
Team Name: Group 55
Team Members: Diksha Kushwah, Jason Nguyen, Joseph Cardillo

Project Overview
This project implements Dijkstra's algorithm to find the shortest path between airports worldwide using the OpenFlights Global Airline Dataset. The program can analyze over 10,000 airports, ferry terminals, and train stations to compute optimal routes.

Features
Load and process 10,000+ airport locations from real-world data
Find shortest path between any two airports using Dijkstra's algorithm
Calculate distances using the Haversine formula (great-circle distance)
Display complete route with intermediate stops and distances
Search airports by IATA code
Interactive command-line interface
Data Source
OpenFlights Global Airline Dataset

Source:https://github.com/jpatokal/openflights
File used: airports.dat
Contains: Airport ID, Name, City, Country, IATA code, Latitude, Longitude
Technologies Used
Language: C++17
Build System: CMake
Data Structures:
Graph (Adjacency List)
Priority Queue (Binary Heap via std::priority_queue)
Hash Maps (std::unordered_map)
Algorithms:
Dijkstra's Shortest Path Algorithm
Haversine Distance Formula
Installation & Setup
Prerequisites
C++ compiler (g++, clang, or MSVC)
CMake (version 3.10 or higher)
Git
Download Data
Download airports.dat from https://github.com/jpatokal/openflights
Place it in the data/ directory
Build Instructions
bash
# Clone the repository
git clone <your-repo-url>
cd shortest-path-finder

# Create build directory
mkdir build
cd build

# Build the project
cmake ..
make

# Run the program
./pathfinder
Alternative Build (without CMake)
bash
# Compile directly
g++ -std=c++17 src/main.cpp src/Graph.cpp src/Dijkstra.cpp -o pathfinder

# Run
./pathfinder
Usage
Start the program: Run ./pathfinder
Choose an option:
Option 1: Find shortest path between two airports
Option 2: Search for airport by IATA code
Option 3: Exit
Example Usage
Enter choice: 1
Enter source airport code (e.g., LAX): LAX
Enter destination airport code (e.g., JFK): JFK

✈️  SHORTEST PATH FOUND!
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Total Distance: 3974.32 km
Number of Stops: 0

Route:
1. LAX - Los Angeles International Airport (Los Angeles, United States)
   ↓ 3974.32 km
2. JFK - John F Kennedy International Airport (New York, United States)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Project Structure
shortest-path-finder/
├── README.md
├── CMakeLists.txt
├── data/
│   └── airports.dat
├── src/
│   ├── main.cpp           # Main program and user interface
│   ├── Graph.h            # Graph class declaration
│   ├── Graph.cpp          # Graph implementation
│   ├── Dijkstra.h         # Dijkstra algorithm declaration
│   └── Dijkstra.cpp       # Dijkstra implementation
└── tests/
Algorithm Complexity
Dijkstra's Algorithm
Time Complexity: O((V + E) log V) where V = vertices (airports), E = edges (connections)
Space Complexity: O(V + E)
Distance Calculation (Haversine)
Time Complexity: O(1)
Space Complexity: O(1)
Graph Building
Time Complexity: O(V² log V) for finding and sorting nearest neighbors
Space Complexity: O(V * E)
Contributors
Diksha Kushwah - Whole Project
Video Demo
[Link to YouTube Video] (To be added)

License
This project is for educational purposes as part of COP3530 Data Structures and Algorithms course.

References
OpenFlights Airport Database: https://github.com/jpatokal/openflights
Dijkstra's Algorithm: Cormen, T. H., et al. "Introduction to Algorithms"
Haversine Formula: https://en.wikipedia.org/wiki/Haversine_formula
C++ STL Documentation: https://cplusplus.com/reference/

