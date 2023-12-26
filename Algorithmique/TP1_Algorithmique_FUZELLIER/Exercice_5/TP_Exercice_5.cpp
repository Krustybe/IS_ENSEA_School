#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

using namespace std;

// Définition de la classe Graph
class Graph {
public:
    int vertices;  // Nombre de sommets dans le graphe
    vector<unordered_set<int>> adjList;  // Liste d'adjacence pour représenter le graphe

    // Constructeur qui initialise le nombre de sommets et la liste d'adjacence
    Graph(int n) {
        vertices = n;
        adjList.resize(n);
    }

    // Méthode pour ajouter une arête entre les sommets u et v
    void addEdge(int u, int v) {
        adjList[u].insert(v);
        adjList[v].insert(u);
    }

    // Méthode de recherche en profondeur (DFS) pour trouver les composantes connexes
    void DFS(int v, vector<bool>& visited, unordered_set<int>& component) {
        visited[v] = true;
        component.insert(v);

        // Parcours des voisins du sommet v
        for (int neighbor : adjList[v]) {
            if (!visited[neighbor]) {
                DFS(neighbor, visited, component);
            }
        }
    }

    // Méthode pour trouver toutes les composantes connexes du graphe
    vector<unordered_set<int>> findConnectedComponents() {
        vector<bool> visited(vertices, false);  // Tableau pour suivre les sommets visités
        vector<unordered_set<int>> components;   // Vecteur pour stocker les composantes connexes

        // Parcours de tous les sommets du graphe
        for (int v = 0; v < vertices; ++v) {
            if (!visited[v]) {
                unordered_set<int> component;  // Nouvelle composante connexe
                DFS(v, visited, component);
                components.push_back(component);  // Ajout de la composante au vecteur
            }
        }

        return components;
    }
};

// Fonction principale
int main() {
    ifstream infile("INPCONGRAPH.txt");   // Fichier d'entrée
    ofstream outfile("OUTCONGRAPH.txt");  // Fichier de sortie

    int n, m;
    infile >> n >> m;  // Lecture du nombre de sommets et d'arêtes

    Graph graph(n);  // Création d'une instance du graphe

    // Lecture des arêtes et ajout au graphe
    for (int i = 0; i < m; ++i) {
        int u, v;
        infile >> u >> v;
        graph.addEdge(u - 1, v - 1);  // Les sommets sont indexés à partir de 1, mais le code utilise 0-indexing
    }

    infile.close();  // Fermeture du fichier d'entrée

    // Recherche des composantes connexes dans le graphe
    vector<unordered_set<int>> components = graph.findConnectedComponents();

    outfile << components.size() << endl;  // Écriture du nombre total de composantes connexes

    // Écriture des composantes connexes dans le fichier de sortie
    for (int i = 0; i < components.size(); ++i) {
        outfile << "composante connexe " << i + 1 << endl;

        // Écriture des sommets de la composante
        for (int vertex : components[i]) {
            outfile << vertex + 1 << " ";  // Ajout de 1 pour revenir à l'indexation à partir de 1
        }

        outfile << endl;
    }

    outfile.close();  // Fermeture du fichier de sortie

    return 0;
}
