"""Algorithme de Welsh-Powell appliqué à un graphe NetworkX."""
import networkx as nx
import matplotlib.pyplot as plt


def welsh_powell(G):
    ordre = sorted(G.nodes(), key=lambda v: (-G.degree(v), str(v)))
    couleurs = {}
    couleur = 0
    for sommet in ordre:
        if sommet in couleurs:
            continue
        couleurs[sommet] = couleur
        for autre in ordre:
            if autre not in couleurs and not G.has_edge(sommet, autre):
                # Vérifier tous les sommets déjà placés dans cette classe de couleur.
                if all(not G.has_edge(autre, v) for v, c in couleurs.items() if c == couleur):
                    couleurs[autre] = couleur
        couleur += 1
    return couleurs


if __name__ == "__main__":
    G = nx.cycle_graph(7)
    couleurs = welsh_powell(G)
    print("Nombre de couleurs :", len(set(couleurs.values())))
    print("Couleurs par sommet :", couleurs)
    pos = nx.spring_layout(G, seed=7)
    nx.draw(G, pos, with_labels=True,
            node_color=[couleurs[v] for v in G.nodes()], cmap=plt.cm.tab10,
            edge_color="gray")
    plt.title("Coloration Welsh-Powell")
    plt.show()
