#include "Grid.h"
#include <iostream>
#include <fstream>

// Constructeur par défaut : initialise une grille vide
Grid::Grid() : rows(0), cols(0) {}

// Constructeur avec dimensions spécifiques : initialise la grille avec des cellules mortes
Grid::Grid(int rows, int cols) : rows(rows), cols(cols) {
    data.resize(rows, std::vector<Cellule>(cols)); // Redimensionne la grille avec des cellules mortes
}

// Méthode pour charger les données depuis un fichier
void Grid::loadFromFile(const std::string& filename) {
    std::ifstream file(filename); // Ouvre le fichier pour lecture
    if (!file.is_open()) { // Vérifie si le fichier a été ouvert correctement
        std::cerr << "Erreur: Impossible d'ouvrir le fichier " << filename << std::endl;
        return;
    }

    // Lit les dimensions de la grille (lignes et colonnes)
    file >> rows >> cols;

    // Redimensionne la matrice de données pour correspondre aux dimensions lues
    data.resize(rows, std::vector<Cellule>(cols));

    // Lit les valeurs de la grille depuis le fichier et met à jour les cellules
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int value;
            file >> value; // Lit la valeur de chaque cellule (0 ou 1)
            data[i][j].setEtat(value == 1); // Met à jour l'état de la cellule (vivante ou morte)
        }
    }

    file.close(); // Ferme le fichier après la lecture
}

// Méthode pour afficher la grille
void Grid::display() const {
    std::cout << "Dimensions: " << rows << "x" << cols << std::endl; // Affiche les dimensions de la grille
    for (const auto& row : data) { // Parcourt chaque ligne de la grille
        for (const auto& cell : row) { // Parcourt chaque cellule dans la ligne
            std::cout << cell << " "; // Affiche l'état de la cellule (vivante/morte)
        }
        std::cout << std::endl; // Nouvelle ligne après chaque ligne de cellules
    }
}

// Méthode pour obtenir une cellule spécifique
const Cellule& Grid::getCell(int x, int y) const {
    return data[x][y]; // Retourne la cellule située aux coordonnées (x, y)
}

// Méthode pour modifier l'état d'une cellule spécifique
void Grid::setCell(int x, int y, bool vivante) {
    data[x][y].setEtat(vivante); // Met à jour l'état de la cellule (vivante ou morte)
}

// Méthode pour obtenir le nombre de lignes de la grille
int Grid::getRows() const {
    return rows; // Retourne le nombre de lignes
}

// Méthode pour obtenir le nombre de colonnes de la grille
int Grid::getCols() const {
    return cols; // Retourne le nombre de colonnes
}
