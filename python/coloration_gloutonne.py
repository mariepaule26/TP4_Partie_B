"""Coloration gloutonne par retour arrière, corrigée à partir du code fourni."""
import networkx as nx
import matplotlib.pyplot as plt


def coloration_retour_arriere(G, nombre_couleurs):
    sommets = list(G.nodes())
    couleurs = {v: -1 for v in sommets}

    def est_valide(v, couleur):
        return all(couleurs[w] != couleur for w in G.neighbors(v))

    def chercher(i):
        if i == len(sommets):
            return True
        v = sommets[i]
        for couleur in range(nombre_couleurs):
            if est_valide(v, couleur):
                couleurs[v] = couleur
                if chercher(i + 1):
                    return True
                couleurs[v] = -1  # indispensable : annuler le choix en cas d'échec
        return False

    return couleurs if chercher(0) else None


if __name__ == "__main__":
    G = nx.cycle_graph(5)
    resultat = coloration_retour_arriere(G, 3)
    if resultat is None:
        print("Aucune coloration avec ce nombre de couleurs.")
    else:
        print("Coloration :", resultat)
        pos = nx.spring_layout(G, seed=7)
        nx.draw(G, pos, with_labels=True,
                node_color=[resultat[v] for v in G.nodes()], cmap=plt.cm.Set3,
                edge_color="gray")
        plt.title("Coloration par retour arrière")
        plt.show()
