#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <limits>
#include <queue>

using namespace std;

const int INF = numeric_limits<int>::max();

// Structure représentant une arête avec la destination et le poids
struct Edge {
    int destination;
    int weight;
};

// Fonction pour exécuter l'algorithme de Dijkstra
void dijkstra(const vector<vector<Edge>>& graph, int start, int end, vector<int>& distance, vector<int>& parent) {
    // Utilisation d'une file de priorité pour extraire efficacement le nœud avec la distance minimale
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    distance[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        // Extraire le nœud avec la distance minimale
        int u = pq.top().second;
        int dist_u = pq.top().first;
        pq.pop();

        // Ignorer les informations obsolètes
        if (dist_u > distance[u]) {
            continue;
        }

        // Parcourir toutes les arêtes sortantes du nœud u
        for (const Edge& edge : graph[u]) {
            int v = edge.destination;
            int weight = edge.weight;

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
    // Remonter à partir du nœud de destination jusqu'au nœud de départ
    for (int v = end; v != -1; v = parent[v]) {
        path.push_back(v + 1);  // Ajouter 1 pour convertir de l'index 0 à l'index 1
    }
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    // Ouverture des fichiers d'entrée et de sortie
    ifstream infile("INPDIJGRAPH.txt");
    ofstream outfile("OUTDIJGRAPH.txt");

    int n, m, start, end;
    // Lire le nombre de sommets, d'arêtes, le sommet de départ et le sommet d'arrivée
    infile >> n >> m >> start >> end;

    // Initialiser le graphe, les distances et les parents
    vector<vector<Edge>> graph(n);
    vector<int> distance(n, INF);
    vector<int> parent(n, -1);

    // Lire les arêtes et construire le graphe
    for (int i = 0; i < m; ++i) {
        int u, v, weight;
        infile >> u >> v >> weight;
        graph[u - 1].push_back({v - 1, weight});
        graph[v - 1].push_back({u - 1, weight});
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
