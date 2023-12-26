#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <limits>
#include <queue>

using namespace std;

const int INF = numeric_limits<int>::max();

// Fonction pour exécuter l'algorithme de Dijkstra
void dijkstra(const vector<vector<pair<int, int>>>& graph, int start, int end, vector<int>& distance, vector<int>& parent) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    distance[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        int dist_u = pq.top().first;
        pq.pop();

        if (dist_u > distance[u]) {
            continue;  // Ignorer l'information obsolète
        }

        // Parcourir tous les voisins de u
        for (const auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;

            // Mettre à jour la distance si un chemin plus court est trouvé
            if (distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                parent[v] = u;
                pq.push({distance[v], v});
            }
        }
    }
}

// Fonction pour reconstruire le chemin le plus court à partir des parents
vector<int> findShortestPath(int start, int end, const vector<int>& parent) {
    vector<int> path;
    for (int v = end; v != -1; v = parent[v]) {
        path.push_back(v + 1);  // Ajouter 1 pour convertir de l'index 0 à l'index 1
    }
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    // Lecture à partir d'un fichier d'entrée
    ifstream infile("INPDIJGRAPH.txt");
    // Écriture dans un fichier de sortie
    ofstream outfile("OUTDIJGRAPH.txt");

    int n, m, start, end;
    // Lire le nombre de sommets, d'arêtes, le sommet de départ et le sommet d'arrivée
    infile >> n >> m >> start >> end;

    // Initialiser le graphe, les distances et les parents
    vector<vector<pair<int, int>>> graph(n);
    vector<int> distance(n, INF);
    vector<int> parent(n, -1);

    // Lire les arêtes et construire le graphe
    for (int i = 0; i < m; ++i) {
        int u, v, weight;
        infile >> u >> v >> weight;
        graph[u - 1].emplace_back(v - 1, weight);
        graph[v - 1].emplace_back(u - 1, weight);
    }

    // Exécuter l'algorithme de Dijkstra
    dijkstra(graph, start - 1, end - 1, distance, parent);

    // Vérifier s'il y a un chemin possible
    if (distance[end - 1] == INF) {
        outfile << "Pas de chemin possible." << endl;
    } else {
        // Afficher la distance minimale et le chemin
        outfile << distance[end - 1] << endl;
        vector<int> path = findShortestPath(start - 1, end - 1, parent);
        for (int i = 0; i < path.size(); ++i) {
            outfile << path[i];
            if (i < path.size() - 1) {
                outfile << " -> ";
            }
        }
    }

    // Fermer les fichiers
    infile.close();
    outfile.close();

    return 0;
}
