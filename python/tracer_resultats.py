"""Trace le temps d'exécution à partir du CSV produit par benchmark.c."""
import csv
import matplotlib.pyplot as plt

with open("resultats/temps.csv", newline="", encoding="utf-8") as f:
    lignes = list(csv.DictReader(f))

n = [int(x["n"]) for x in lignes]
temps = [float(x["temps_secondes"]) for x in lignes]
plt.plot(n, temps, marker="o", label="Mesures")
plt.xscale("log")
plt.xlabel("Nombre de sommets N (échelle logarithmique)")
plt.ylabel("Temps de calcul (secondes)")
plt.title("Temps d'exécution de Welsh-Powell")
plt.grid(True, which="both", linestyle="--", alpha=0.5)
plt.legend()
plt.tight_layout()
plt.savefig("resultats/complexite.png", dpi=160)
plt.show()
