import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt
import numpy as np
import networkx as nx

# Load the data, skipping the first row - I dont need the number of nodes and edges
data = np.loadtxt('graph.txt', skiprows=1)

# Create a graph
G = nx.Graph()

# Add edges
for i in range(data.shape[0]):
    G.add_edge(int(data[i, 0]), int(data[i, 1]))

# Draw the graph
nx.draw(G, with_labels=True)
plt.show()