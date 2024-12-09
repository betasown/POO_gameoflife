#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>
#include "Cellule.h"

class Grid {
private:
    int rows; // Nombre de lignes dans la grille
    int cols; // Nombre de colonnes dans la grille
    std::vector<std::vector<Cellule>> data; // Matrice de cellules représentant la grille

public:
    // Constructeur par défaut : crée une grille vide
    Grid();

    // Constructeur avec dimensions spécifiques : initialise une grille avec des cellules mortes
    Grid(int rows, int cols);

    // Méthode pour charger les données de la grille depuis un fichier
    void loadFromFile(const std::string& filename);

    // Méthode pour afficher la grille (probablement en mode texte)
    void display() const;

    // Méthode pour obtenir une cellule spécifique en lecture (const)
    const Cellule& getCell(int x, int y) const;

    // Méthode pour modifier l'état d'une cellule spécifique
    void setCell(int x, int y, bool vivante);

    // Méthode pour obtenir le nombre de lignes de la grille
    int getRows() const;

    // Méthode pour obtenir le nombre de colonnes de la grille
    int getCols() const;
};

#endif // GRID_H
