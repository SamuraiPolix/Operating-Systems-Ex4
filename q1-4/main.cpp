#include "euler_circuit.hpp"

/*
1. Create a Graph Data structure (you may use same data structure as ex.3) (10 pts)
2. Implement an Algorithm to find Euler circle (Euler circuit) on the graph or prove one does not exist. (10 pts)
3. Generate Random graph and run the algorithm on it. Receive parameters
    (number of edges, number of vertices, random seed) using argc,argv with getopt(3) - same as ex.1 (10 pts)
4. Provide code coverage reports, gprof, Valgrind/memcheck report and Valgrind callGraph for your code, (20 pts)
 */

int main(int argc, char* argv[]) {
    // Default values for command-line arguments
    int num_vertices = 0;
    int num_edges = 0;
    unsigned int seed = time(0);

    // Parse command-line arguments using getopt
    int opt;
    while ((opt = getopt(argc, argv, "n:e:s:")) != -1) {
        switch (opt) {
            case 'n':
                num_vertices = atoi(optarg);
                break;
            case 'e':
                num_edges = atoi(optarg);
                break;
            case 's':
                seed = (unsigned int)atoi(optarg);
                break;
            default:
                std::cerr << "Usage: " << argv[0] << " -n num_vertices -e num_edges -s seed" << std::endl;
                return 1;
        }
    }

    // Validate the number of vertices and edges
    if (num_vertices <= 0) {
        std::cerr << "Number of vertices must be positive." << std::endl;
        return 1;
    }

    int max_edges = num_vertices * (num_vertices - 1) / 2;
    if (num_edges > max_edges) {
        std::cerr << "Too many edges for the number of vertices." << std::endl;
        return 1;
    }

    if (num_edges < 0) {
        std::cerr << "Number of edges cannot be negative." << std::endl;
        return 1;
    }

    // Create the graph with the specified number of vertices
    Graph graph(num_vertices);

    // Task 3: Generate Random Graph and Run the Algorithm
    // The random graph is generated based on the input parameters

    // Generate random edges for the graph
    graph.generateRandomEdges(num_edges, seed);

    // Find the Euler circuit in the graph
    std::vector<int> circuit = graph.findEulerCircuit();

    // Output the Euler circuit or indicate if it doesn't exist
    graph.printEulerCircuit(circuit);

    return 0;
}
