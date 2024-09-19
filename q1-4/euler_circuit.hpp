#ifndef EULER_CIRCUIT_HPP
#define EULER_CIRCUIT_HPP

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <stack>
#include <string>
#include <getopt.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>

// Graph class definition
class Graph {
private:
    int num_vertices;                     // Number of vertices in the graph
    std::vector<std::list<int>> adj;      // Adjacency list representation
    
public:
    // Constructor to init a graph with the given number of vertices (no edges yet)
    Graph(int num_vertices);

    // Add an undirected edge between vertices u and v
    void addEdge(int u, int v);

    // Generate random edges for the graph based on the given number of edges and seed
    void generateRandomEdges(int num_edges, unsigned int seed);

    // Check if the graph is connected
    bool isConnected();

    // Check if the graph has an Euler circuit
    bool hasEulerCircuit();

    // Find and return the Euler circuit using Hierholzer's algorithm
    std::vector<int> findEulerCircuit();

    // Print the Euler circuit or indicate if it doesn't exist
    void printEulerCircuit(const std::vector<int>& circuit);

private:
    // Helper DFS function to visit all vertices connected to v
    void DFS(int v, std::vector<bool>& visited);
};

#endif // EULER_CIRCUIT_HPP
