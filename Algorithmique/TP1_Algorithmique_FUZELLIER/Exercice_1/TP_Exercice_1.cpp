#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

// Fonction qui réalise l'exercice 1
void Exercice1()
{
    int X;  // Variable pour stocker le nombre saisi par l'utilisateur
    int A = 1;  // Variable pour effectuer des calculs successifs
    int M = 0;  // Variable pour compter le nombre d'itérations

    // Demande à l'utilisateur d'entrer un nombre
    std::cout << "Entrez le nombre X : ";
    std::cin >> X;

    // Boucle tant que A est inférieur à X
    while (A < X) {
        A = A * 2;  // Multiplie A par 2 à chaque itération
        M++;  // Incrémente le compteur d'itérations
    }

    std::cout << "1";  // Affiche "1" (partie initiale du résultat)

    // Boucle pour afficher les '*2' M fois
    for (int i = 0; i < M; i++) {
        std::cout << " * 2";
    }

    std::cout << " / 3 * 2 = " << X << std::endl;  // Affiche le résultat final
}

// Fonction principale
int main()
{
    Exercice1();  // Appelle la fonction Exercice1 pour exécuter l'exercice
    return 0;
}
