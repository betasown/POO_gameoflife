#ifndef CELLULE_H
#define CELLULE_H

#include <ostream> // Nécessaire pour utiliser std::ostream (affichage avec <<)

// Définition de la classe Cellule
class Cellule {
private:
    bool vivante; // Indique si la cellule est vivante (true) ou morte (false)

public:
    // Constructeur par défaut : initialise une cellule morte
    Cellule();

    // Constructeur avec paramètre : permet de définir l'état initial
    Cellule(bool vivante);

    // Modifie l'état de la cellule (vivante ou morte)
    void setEtat(bool vivante);

    // Retourne l'état de la cellule (true = vivante, false = morte)
    bool estVivante() const;

    // Permet d'afficher une cellule avec << (par exemple : std::cout << cellule)
    // Cette fonction est définie comme "friend" pour accéder à l'attribut privé "vivante"
    friend std::ostream& operator<<(std::ostream& os, const Cellule& cell);
};

#endif // CELLULE_H
