#include "euler_circuit.hpp"

Graph::Graph(int num_vertices) : num_vertices(num_vertices), adj(num_vertices) {}   // adj is a vector of num_vertices lists

void Graph::addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void Graph::generateRandomEdges(int num_edges, unsigned int seed) {
    srand(seed);
    std::set<std::pair<int, int>> edge_set;

    // make sure the num of edges is not too large (negative is already checked in main)
    int max_edges = num_vertices * (num_vertices - 1) / 2;
    if (num_edges > max_edges) {
        std::cerr << "Too many edges for the number of vertices." << std::endl;
        exit(1);
    }

    // Start by connecting all vertices into a cycle (to ensure basic connectivity)
    std::cout << "Generating cycle to ensure connectivity:\n";
    for (int i = 0; i < num_vertices; ++i) {
        int u = i;
        int v = (i + 1) % num_vertices;  // Connect in a cycle
        edge_set.insert(std::make_pair(std::min(u, v), std::max(u, v)));
        addEdge(u, v);
        std::cout << "Added edge: " << u << " -> " << v << "\n";
    }

    // Add remaining edges randomly
    std::cout << "\nAdding random edges to reach " << num_edges << " edges:\n";
    while ((int)edge_set.size() < num_edges) {
        int u = rand() % num_vertices;
        int v = rand() % num_vertices;
        if (u == v) continue;  // Avoid self-loops
        int a = std::min(u, v);
        int b = std::max(u, v);
        if (edge_set.count(std::make_pair(a, b)) == 0) {
            edge_set.insert(std::make_pair(a, b));
            addEdge(u, v);
            std::cout << "Added edge: " << u << " -> " << v << "\n";
        }
    }

    // Print degrees of all vertices
    std::cout << "\nDegrees of vertices after edge generation:\n";
    for (int i = 0; i < num_vertices; ++i) {
        std::cout << "Vertex " << i << ": Degree " << adj[i].size() << "\n";
    }

    // Fix vertices with odd degrees (Euler circuit requires all vertices to have even degrees)
    std::vector<int> odd_degree_vertices;
    for (int i = 0; i < num_vertices; ++i) {
        if (adj[i].size() % 2 != 0) {
            odd_degree_vertices.push_back(i);
        }
    }

    // If there are odd-degree vertices, print debug info
    if (!odd_degree_vertices.empty()) {
        std::cout << "\nOdd-degree vertices found: ";
        for (int v : odd_degree_vertices) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }

    // If there are odd-degree vertices, we pair them up to ensure even degree
    std::cout << "\nAttempting to fix odd-degree vertices:\n";
    while (odd_degree_vertices.size() >= 2) {
        bool edge_added = false;
        for (size_t i = 0; i < odd_degree_vertices.size(); ++i) {
            for (size_t j = i + 1; j < odd_degree_vertices.size(); ++j) {
                int u = odd_degree_vertices[i];
                int v = odd_degree_vertices[j];
                
                // Ensure that the edge does not already exist
                int a = std::min(u, v);
                int b = std::max(u, v);
                if (edge_set.count(std::make_pair(a, b)) == 0) {
                    edge_set.insert(std::make_pair(a, b));
                    addEdge(u, v);
                    std::cout << "Added edge to fix odd degree: " << u << " -> " << v << "\n";

                    // Remove the vertices that are now even-degree
                    odd_degree_vertices.erase(odd_degree_vertices.begin() + j);
                    odd_degree_vertices.erase(odd_degree_vertices.begin() + i);
                    edge_added = true;
                    break;
                }
            }
            if (edge_added) break;
        }
        if (!edge_added) {
            std::cerr << "Error: Unable to connect any odd-degree vertices without duplicating edges." << std::endl;
            break;
        }
    }

    // Final check: if there are still odd-degree vertices, we have an issue
    if (!odd_degree_vertices.empty()) {
        std::cerr << "Error: Unable to fix all odd-degree vertices. Odd-degree vertices left: ";
        for (int v : odd_degree_vertices) {
            std::cerr << v << " ";
        }
        std::cerr << std::endl;
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
