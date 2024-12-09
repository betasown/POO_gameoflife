#include "Cellule.h"
#include <iostream> // Nécessaire pour l'utilisation de std::ostream

// Constructeur par défaut : initialise la cellule comme morte (vivante = false)
Cellule::Cellule() : vivante(false) {}

// Constructeur avec état initial : permet de définir si la cellule est vivante ou morte
Cellule::Cellule(bool vivante) : vivante(vivante) {}

// Modifie l'état de la cellule
void Cellule::setEtat(bool vivante) {
    this->vivante = vivante; // Met à jour l'attribut "vivante" avec la nouvelle valeur
}

// Retourne l'état actuel de la cellule (vivante ou morte)
bool Cellule::estVivante() const {
    return vivante; // Renvoie true si vivante, false sinon
}

// Permet d'afficher l'état de la cellule avec << (1 pour vivante, 0 pour morte)
std::ostream& operator<<(std::ostream& os, const Cellule& cell) {
    os << (cell.vivante ? "1" : "0"); // Affiche "1" si vivante, "0" si morte
    return os; // Retourne le flux pour permettre les affichages chaînés
}
