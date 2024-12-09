#ifndef JEU_H
#define JEU_H

#include "Grid.h"   // Inclut la classe Grid pour la gestion de la grille
#include "Fichier.h" // Inclut la classe Fichier pour la gestion des fichiers
#include <string>   // Pour l'utilisation de std::string

class Jeu {
private:
    Grid grid; // Instance de la grille, représente l'état actuel du jeu
    std::string grillePrecedente; // Représentation de la grille précédente sous forme de chaîne
    Fichier gestionnaireFichier; // Instance permettant la gestion des fichiers (sauvegarde, etc.)

    // Méthode privée pour convertir la grille en une chaîne (utilisée pour vérifier les cycles)
    std::string convertirGrilleEnChaine() const;

public:
    // Constructeur : prend une grille initiale et un gestionnaire de fichier
    Jeu(const Grid& grilleInitiale, const Fichier& fichier);

    // Méthode pour exécuter une itération du jeu (mettre à jour la grille)
    void prochaineIteration();

    // Méthode pour afficher l'état actuel de la grille
    void afficherGrille() const;

    // Méthode pour vérifier si la grille actuelle est identique à la précédente (détecte les cycles)
    bool estIdentiqueALaPrecedente();

    // Méthode pour sauvegarder la grille actuelle via la classe Fichier
    void sauvegarderGrille(int iteration) const;

    // Méthode pour obtenir la grille actuelle
    const Grid& getGrid() const;
};

#endif // JEU_H
