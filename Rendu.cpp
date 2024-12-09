#include "Rendu.h"
using namespace sf;

// Constructeur avec couleurs par défaut
Rendu::Rendu(int largeurFenetre, int hauteurFenetre, int tailleCellule)
    : window(VideoMode(largeurFenetre, hauteurFenetre), "Jeu de la Vie GROUPE 6 SFML"), // Création de la fenêtre avec SFML
    cellSize(tailleCellule), // Taille des cellules
    couleurVivante(Color::Red), // Couleur des cellules vivantes (noir)
    couleurMorte(Color::White), // Couleur des cellules mortes (blanc)
    couleurFond(Color::Black) { // Couleur de fond de la fenêtre (noir)
    window.setFramerateLimit(60); // Limite le taux de rafraîchissement à 60 FPS
}

// Méthode pour dessiner la grille dans la fenêtre
void Rendu::dessinerGrille(const Grid& grille) {
    int rows = grille.getRows(); // Récupère le nombre de lignes
    int cols = grille.getCols(); // Récupère le nombre de colonnes

    window.clear(couleurFond); // Efface la fenêtre et applique la couleur de fond

    for (int x = 0; x < rows; ++x) { // Parcourt chaque ligne de la grille
        for (int y = 0; y < cols; ++y) { // Parcourt chaque colonne de la grille
            // Création d'une cellule sous forme de rectangle avec une taille de cellule donnée
            sf::RectangleShape cell(Vector2f(static_cast<float>(cellSize - 1), static_cast<float>(cellSize - 1)));
            cell.setPosition(static_cast<float>(y * cellSize), static_cast<float>(x * cellSize)); // Positionne la cellule sur la fenêtre

            // Détermine si la cellule est vivante ou morte
            if (grille.getCell(x, y).estVivante()) {
                cell.setFillColor(couleurVivante); // Cellule vivante (noire)
            }
            else {
                cell.setFillColor(couleurMorte); // Cellule morte (blanche)
            }

            window.draw(cell); // Dessine la cellule dans la fenêtre
        }
    }
}

// Méthode pour afficher la fenêtre
void Rendu::afficher() {
    window.display(); // Affiche le contenu de la fenêtre
}

// Méthode pour gérer les événements
bool Rendu::estOuverte() {
    sf::Event event;
    while (window.pollEvent(event)) { // Vérifie s'il y a des événements dans la fenêtre
        if (event.type == Event::Closed) { // Si l'événement est la fermeture de la fenêtre
            window.close(); // Ferme la fenêtre
            return false; // Indique que la fenêtre est fermée
        }
    }
    return true; // La fenêtre est toujours ouverte
}

// Méthode pour attendre entre les itérations
void Rendu::attendre(int milliseconds) const {
   sf::sleep(sf::milliseconds(milliseconds)); // Fait une pause pendant un certain nombre de millisecondes
}
