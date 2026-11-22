"""Reprise du premier exemple du sujet : création et affichage d'un graphe."""
import networkx as nx
import matplotlib.pyplot as plt

G = nx.Graph()
G.add_nodes_from([1, 2, 3, 4, 5])
G.add_edges_from([(1, 2), (2, 3), (3, 4), (4, 5), (5, 1)])
pos = nx.spring_layout(G, seed=7)
nx.draw(G, pos, with_labels=True, node_color="lightblue", edge_color="gray")
plt.title("Graphe de démonstration")
plt.tight_layout()
plt.show()
