#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

// Fonction pour trouver la sous-séquence monotone croissante la plus longue
void Exercice2(const vector<int>& A, vector<int>& result) {
    int n = A.size();
    vector<int> dp(n, 1);  // Tableau de programmation dynamique pour stocker les longueurs des sous-séquences

    // Parcours de la séquence et mise à jour du tableau dp
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            // Si l'élément actuel est plus grand que l'élément précédent
            // et si la longueur de la sous-séquence jusqu'à l'élément actuel est plus grande,
            // alors mettez à jour la longueur de la sous-séquence
            if (A[i] > A[j] && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
            }
        }
    }

    // Trouver la longueur maximale
    int maxLength = *max_element(dp.begin(), dp.end());

    // Reconstruire la sous-séquence à partir du tableau dp
    for (int i = n - 1; i >= 0; --i) {
        if (dp[i] == maxLength) {
            result.push_back(A[i]);
            --maxLength;
        }
    }

    reverse(result.begin(), result.end());
}

int main() {
    ifstream inputFile("INPMONOSEQ.txt");    // Ouvrir le fichier d'entrée
    ofstream outputFile("OUTMONOSEQ.txt");   // Ouvrir le fichier de sortie

    int n;
    inputFile >> n;  // Lire le nombre d'éléments dans la séquence

    vector<int> A(n);
    for (int i = 0; i < n; ++i) {
        inputFile >> A[i];  // Lire les éléments de la séquence
    }

    vector<int> result;
    Exercice2(A, result);  // Appeler la fonction pour trouver la sous-séquence

    // Écrire la sortie dans le fichier OUTMONOSEQ.TXT
    outputFile << result.size() << endl;  // Écrire la longueur de la sous-séquence
    for (int i : result) {
        outputFile << "a[" << i + 1 << "] = " << result[i] << endl;  // Écrire les éléments de la sous-séquence
    }

    inputFile.close();   // Fermer le fichier d'entrée
    outputFile.close();  // Fermer le fichier de sortie

    return 0;
}
