#include "Jeu.h"
#include <sstream>

// Constructeur de la classe Jeu
Jeu::Jeu(const Grid& grilleInitiale, const Fichier& fichier)
    : grid(grilleInitiale), gestionnaireFichier(fichier) {
    // Initialisation de la grille précédente avec la grille initiale convertie en chaîne
    grillePrecedente = convertirGrilleEnChaine();
}

// Convertir la grille actuelle en une chaîne unique représentant l'état des cellules
std::string Jeu::convertirGrilleEnChaine() const {
    std::ostringstream oss;
    int rows = grid.getRows();
    int cols = grid.getCols();

    // Parcours de toutes les cellules de la grille pour construire la chaîne
    for (int x = 0; x < rows; ++x) {
        for (int y = 0; y < cols; ++y) {
            oss << (grid.getCell(x, y).estVivante() ? "1" : "0"); // "1" si vivante, "0" sinon
        }
        oss << "\n"; // Nouvelle ligne à chaque fin de ligne de la grille
    }

    return oss.str(); // Retourne la chaîne construite
}

// Exécuter une itération du jeu (mettre à jour la grille en fonction des règles)
void Jeu::prochaineIteration() {
    int rows = grid.getRows();
    int cols = grid.getCols();

    Grid nouvelleGrille(rows, cols); // Crée une nouvelle grille vide pour la prochaine itération

    // Parcours de chaque cellule de la grille actuelle
    for (int x = 0; x < rows; ++x) {
        for (int y = 0; y < cols; ++y) {
            int voisinsVivants = 0;

            // Compte le nombre de voisins vivants en tenant compte des bords toriques
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    if (dx == 0 && dy == 0) continue; // Ignore la cellule elle-même

                    // Calcul des indices des voisins en tenant compte des bords toriques
                    int nx = (x + dx + rows) % rows;
                    int ny = (y + dy + cols) % cols;

                    // Si le voisin est vivant, incrémente le compteur
                    if (grid.getCell(nx, ny).estVivante()) {
                        ++voisinsVivants;
                    }
                }
            }

            // Applique les règles du jeu de la vie pour chaque cellule
            const Cellule& cell = grid.getCell(x, y);
            if (cell.estVivante()) {
                // Une cellule vivante reste vivante si elle a 2 ou 3 voisins vivants
                nouvelleGrille.setCell(x, y, voisinsVivants == 2 || voisinsVivants == 3);
            }
            else {
                // Une cellule morte devient vivante si elle a exactement 3 voisins vivants
                nouvelleGrille.setCell(x, y, voisinsVivants == 3);
            }
        }
    }

    // Remplace la grille actuelle par la nouvelle grille mise à jour
    grid = nouvelleGrille;
}

// Afficher l'état actuel de la grille
void Jeu::afficherGrille() const {
    grid.display(); // Appelle la méthode display() de la classe Grid pour afficher la grille
}

// Vérifie si la génération actuelle est identique à la précédente (pour détecter les cycles)
bool Jeu::estIdentiqueALaPrecedente() {
    std::string grilleActuelle = convertirGrilleEnChaine();
    if (grilleActuelle == grillePrecedente) {
        return true; // Si les grilles sont identiques, retourner true
    }
    // Sinon, mettre à jour la grille précédente avec l'état actuel
    grillePrecedente = grilleActuelle;
    return false;
}

// Sauvegarde l'état actuel de la grille dans un fichier via la classe Fichier
void Jeu::sauvegarderGrille(int iteration) const {
    std::string grille = convertirGrilleEnChaine();
    gestionnaireFichier.sauvegarderGrille(grille, iteration); // Sauvegarde la grille dans un fichier
}

// Retourne la grille actuelle
const Grid& Jeu::getGrid() const {
    return grid;
}
