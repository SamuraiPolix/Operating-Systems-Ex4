#include "euler_circuit.hpp"

Graph::Graph(int num_vertices) : num_vertices(num_vertices), adj(num_vertices) {}   // adj is a vector of num_vertices lists

Graph::~Graph() {
    adj.clear();
}

void Graph::addEdge(int u, int v) {
    adj[u].insert(v);
    adj[v].insert(u);
}

void Graph::generateRandomEdges(int num_edges, unsigned int seed) {
    srand(seed);
    
    int edge_count = 0;
    while (edge_count < num_edges) {
        int u = rand() % num_vertices;
        int v = rand() % num_vertices;

        // Ensure no self-loop and no duplicate edge
        if (u != v && std::find(adj[u].begin(), adj[u].end(), v) == adj[u].end()) {
            addEdge(u, v);
            edge_count++;
        }
    }
}

// DFS - Search utility function to check connectivity
void Graph::DFS(int v, std::vector<bool>& visited) {
    visited[v] = true;
    for (int u : adj[v]) {
        if (!visited[u]) {
            DFS(u, visited);
        }
    }
}

// Function to check if the graph is connected, uses DFS
bool Graph::isConnected() {
    std::vector<bool> visited(num_vertices, false);

    // Find a vertex with non-zero degree
    int non_zero_degree_vertex = -1;
    for (int i = 0; i < num_vertices; ++i) {
        if (!adj[i].empty()) {
            non_zero_degree_vertex = i;
            break;
        }
    }

    // If there are no edges, the graph is considered connected
    if (non_zero_degree_vertex == -1)
        return true;

    // Start DFS from a vertex with non-zero degree
    DFS(non_zero_degree_vertex, visited);

    // Check if all non-zero degree vertices are visited
    for (int i = 0; i < num_vertices; ++i) {
        if (!adj[i].empty() && !visited[i]) {
            return false;
        }
    }

    return true;
}

// Function to check if the graph has an Euler circuit
bool Graph::hasEulerCircuit() {
    if (!isConnected())
        return false;

    // Check if all vertices have even degree
    for (int i = 0; i < num_vertices; ++i) {
        if (adj[i].size() % 2 != 0)
            return false;
    }

    return true;
}

// Function to find and return the Euler circuit using Hierholzer's algorithm
std::vector<int> Graph::findEulerCircuit() {
    std::vector<int> circuit;

    if (!hasEulerCircuit())
        return circuit;

    std::cout << "Euler circuit exists." << std::endl;

    // Create a copy of adjacency lists to modify during the algorithm
    std::vector<std::multiset<int>> adj_copy(num_vertices);
    for (int i = 0; i < num_vertices; ++i) {
        for (int v : adj[i]) {
            adj_copy[i].insert(v);
        }
    }

    // Start from a vertex with non-zero degree
    int curr_v = 0;
    for (int i = 0; i < num_vertices; ++i) {
        if (!adj[i].empty()) {
            curr_v = i;
            break;
        }
    }

    std::stack<int> curr_path;
    curr_path.push(curr_v);

    while (!curr_path.empty()) {
        if (!adj_copy[curr_v].empty()) {
            curr_path.push(curr_v);
            int next_v = *adj_copy[curr_v].begin();
            // Remove the edge between curr_v and next_v
            adj_copy[curr_v].erase(adj_copy[curr_v].find(next_v));
            adj_copy[next_v].erase(adj_copy[next_v].find(curr_v));
            curr_v = next_v;
        } else {
            circuit.push_back(curr_v);
            curr_v = curr_path.top();
            curr_path.pop();
        }
    }

    return circuit;
}

// Function to print the Euler circuit
void Graph::printEulerCircuit(const std::vector<int>& circuit) {
    if (circuit.empty()) {
        std::cout << "Euler circuit does not exist in the graph." << std::endl;
        return;
    }

    std::cout << "Euler circuit exists. The circuit is:" << std::endl;
    for (auto it = circuit.rbegin(); it != circuit.rend(); ++it) {
        std::cout << *it;
        if (it + 1 != circuit.rend()) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
}

# include <fstream>

void Graph::show(){
    // export the graph to txt and run python file in another thread to show it
    std::ofstream out("graph.txt");
    out << num_vertices << std::endl;
    for (int i = 0; i < num_vertices; ++i) {
        for (int v : adj[i]) {
            out << i << " " << v << std::endl;
        }
    }
    out.close();

    system("python3 show_graph.py"); 

    // remove the file after showing
    remove("graph.txt");
}