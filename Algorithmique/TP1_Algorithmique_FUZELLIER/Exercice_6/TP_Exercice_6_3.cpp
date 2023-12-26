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

// Structure représentant un nœud dans le tas binaire utilisé pour l'algorithme de Dijkstra
struct MinHeapNode {
    int vertex;
    int distance;
};

// Classe implémentant un tas binaire (Heap) pour l'algorithme de Dijkstra
class MinHeap {
public:
    MinHeap(int capacity);
    void insertKey(MinHeapNode key);
    MinHeapNode extractMin();
    bool isEmpty();

private:
    vector<MinHeapNode> heap;  // Vecteur pour stocker les nœuds du tas binaire
    vector<int> position;      // Vecteur pour stocker la position de chaque nœud dans le tas
    int capacity;              // Capacité maximale du tas binaire
    void heapify(int i);       // Fonction pour maintenir la propriété du tas
};

// Constructeur du tas binaire
MinHeap::MinHeap(int capacity) {
    this->capacity = capacity;
    heap.resize(capacity);
    position.resize(capacity, -1);
}

// Insérer une clé dans le tas binaire
void MinHeap::insertKey(MinHeapNode key) {
    int i = heap.size();
    heap.push_back(key);
    position[key.vertex] = i;

    // Maintenir la propriété du tas
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap[parent].distance > heap[i].distance) {
            swap(heap[i], heap[parent]);
            swap(position[heap[i].vertex], position[heap[parent].vertex]);
            i = parent;
        } else {
            break;
        }
    }
}

// Extraire le nœud avec la distance minimale du tas binaire
MinHeapNode MinHeap::extractMin() {
    if (isEmpty()) {
        return { -1, -1 };
    }

    MinHeapNode root = heap[0];
    position[root.vertex] = -1;

    if (heap.size() > 1) {
        heap[0] = heap.back();
        position[heap[0].vertex] = 0;
        heap.pop_back();
        heapify(0);
    } else {
        heap.clear();
    }

    return root;
}

// Maintenir la propriété du tas à l'indice i
void MinHeap::heapify(int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap.size() && heap[left].distance < heap[smallest].distance) {
        smallest = left;
    }

    if (right < heap.size() && heap[right].distance < heap[smallest].distance) {
        smallest = right;
    }

    if (smallest != i) {
        swap(heap[i], heap[smallest]);
        swap(position[heap[i].vertex], position[heap[smallest].vertex]);
        heapify(smallest);
    }
}

// Vérifier si le tas est vide
bool MinHeap::isEmpty() {
    return heap.empty();
}

// Fonction pour exécuter l'algorithme de Dijkstra
void dijkstra(const vector<vector<Edge>>& graph, int start, int end, vector<int>& distance, vector<int>& parent) {
    int n = graph.size();
    MinHeap minHeap(n);

    distance[start] = 0;
    minHeap.insertKey({start, 0});

    while (!minHeap.isEmpty()) {
        MinHeapNode minNode = minHeap.extractMin();
        int u = minNode.vertex;

        for (const Edge& edge : graph[u]) {
            int v = edge.destination;
            int weight = edge.weight;

            if (distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                parent[v] = u;
                minHeap.insertKey({v, distance[v]});
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
    // Ouverture des fichiers d'entrée et de sortie
    ifstream infile("INPDIJGRAPH.txt");
    ofstream outfile("OUTDIJGRAPH.txt");

    int n, m, start, end;
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


/*Le code 6.2 utilise une structure (`Edge`) pour représenter les arêtes du graphe, améliorant la lisibilité.
Le code 6.3, en utilisant une classe personnalisée `MinHeap` pour le tas binaire, offre une encapsulation et
une réutilisabilité potentielles, permettant un contrôle fin sur la structure de données. Ces approches
offrent des avantages en termes de clarté, modularité et personnalisation par rapport au code 6.1. Le choix
entre elles dépend des préférences de conception et des besoins spécifiques du projet.*/