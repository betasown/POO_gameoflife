#ifndef RENDU_H
#define RENDU_H

#include <SFML/Graphics.hpp> // Inclut la bibliothèque SFML pour le rendu graphique
#include "Grid.h"             // Inclut la classe Grid pour la gestion de la grille

class Rendu {
private:
    sf::RenderWindow window;  // Fenêtre pour afficher la grille, utilisant SFML
    int cellSize;             // Taille d'une cellule en pixels pour l'affichage
    sf::Color couleurVivante; // Couleur des cellules vivantes (ex: verte)
    sf::Color couleurMorte;   // Couleur des cellules mortes (ex: noire)
    sf::Color couleurFond;    // Couleur de fond de la fenêtre (ex: blanc)

public:
    // Constructeur : initialisation de la fenêtre et des couleurs, et définition de la taille des cellules
    Rendu(int largeurFenetre, int hauteurFenetre, int tailleCellule);

    // Méthode pour dessiner la grille dans la fenêtre en fonction des cellules vivantes et mortes
    void dessinerGrille(const Grid& grille);

    // Méthode pour afficher la fenêtre (actualise l'affichage)
    void afficher();

    // Méthode pour vérifier si la fenêtre est toujours ouverte (utile pour la boucle de rendu)
    bool estOuverte();

    // Méthode pour gérer la pause entre les itérations (délai entre les affichages)
    void attendre(int milliseconds) const;
};

#endif // RENDU_H
