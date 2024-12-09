#ifndef FICHIER_H
#define FICHIER_H

#include <string>
#include <filesystem> // Pour manipuler les fichiers et dossiers

class Fichier {
private:
    std::string dossierSortie; // Le chemin du dossier où les fichiers de sortie seront enregistrés

public:
    // Constructeur qui définit le dossier de sortie
    explicit Fichier(const std::string& dossier);

    // Méthode pour créer le dossier (avec nettoyage s'il existe déjà)
    void creerDossier();

    // Méthode pour sauvegarder une grille dans un fichier
    void sauvegarderGrille(const std::string& grille, int iteration) const;

    // Accesseur pour obtenir le chemin du dossier de sortie
    std::string getDossierSortie() const;
};

#endif // FICHIER_H
