TP4 - Partie B : coloration de graphes et étude expérimentale

CONTENU
- include/graph0.h : structure et déclarations des fonctions C.
- src/graph0.c : création du graphe, degrés, Welsh-Powell, affichage et export DOT.
- src/main.c : exemple de démonstration.
- src/benchmark.c : génération de graphes aléatoires et mesure des temps.
- python/ : visualisation, coloration par retour arrière, Welsh-Powell et tracé.
- tests/test_graph.c : vérifications simples de la coloration.
- resultats/ : fichiers produits lors de l'exécution.

COMPILATION (terminal PowerShell, à la racine du projet)
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 -Iinclude src/main.c src/graph0.c -o tp4_demo.exe
.\tp4_demo.exe

gcc -std=c11 -Wall -Wextra -Wpedantic -O2 -Iinclude tests/test_graph.c src/graph0.c -o test_graph.exe
.\test_graph.exe

gcc -std=c11 -Wall -Wextra -Wpedantic -O2 -Iinclude src/benchmark.c src/graph0.c -o benchmark.exe
.\benchmark.exe

Le benchmark écrit resultats/temps.csv. Il utilise une matrice d'adjacence : la mémoire
nécessaire est proportionnelle à N². La taille 10 000 demande environ 100 millions
d'octets pour la matrice compacte (unsigned char), hors autres tableaux. Si la mémoire
est limitée, retirer 10000 de la liste sizes dans src/benchmark.c.

PYTHON
Installer les dépendances : py -m pip install networkx matplotlib
Exécuter depuis la racine :
py python/visualisation.py
py python/coloration_gloutonne.py
py python/welsh_powell.py
py python/tracer_resultats.py

ANALYSE
Le temps mesuré porte sur le calcul des degrés, le tri et l'affectation des couleurs,
mais pas sur la génération aléatoire du graphe. La matrice impose déjà un parcours en
O(N²) pour calculer tous les degrés. Le tri à bulles du code d'origine est également
O(N²). La courbe doit être interprétée comme une mesure de cette implémentation précise,
et non comme une preuve mathématique à elle seule.
