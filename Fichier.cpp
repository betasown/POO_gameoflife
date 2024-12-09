#include "Fichier.h"
#include <iostream>
#include <fstream>   // Pour lire/écrire des fichiers
#include <sstream>   // Pour manipuler des chaînes de caractères
#include <filesystem> // Pour gérer les fichiers et répertoires

// Constructeur de la classe Fichier, qui initialise le chemin du dossier de sortie
Fichier::Fichier(const std::string& dossier) : dossierSortie(dossier) {}

// Créer le dossier de sortie, ou le nettoyer s'il existe déjà
void Fichier::creerDossier() {
    namespace fs = std::filesystem; // Alias pour simplifier l'utilisation de filesystem

    try {
        if (fs::exists(dossierSortie)) { // Vérifier si le dossier existe déjà
            // Si le dossier existe, supprimer les fichiers qu'il contient
            for (const auto& entry : fs::directory_iterator(dossierSortie)) {
                fs::remove(entry.path()); // Supprimer chaque fichier du dossier
            }
            std::cout << "Dossier existant '" << dossierSortie << "' nettoye.\n";
        }
        else {
            // Si le dossier n'existe pas, le créer
            fs::create_directories(dossierSortie);
            std::cout << "Dossier '" << dossierSortie << "' cree avec succes.\n";
        }
    }
    catch (const fs::filesystem_error& e) { // En cas d'erreur lors de la gestion du dossier
        std::cerr << "Erreur lors de la gestion du dossier : " << e.what() << "\n";
    }
}

// Sauvegarder une grille dans un fichier
void Fichier::sauvegarderGrille(const std::string& grille, int iteration) const {
    namespace fs = std::filesystem; // Alias pour simplifier l'utilisation de filesystem

    try {
        // Générer le nom du fichier en fonction de l'itération (ex: generation_1.txt)
        std::string filename = dossierSortie + "/generation_" + std::to_string(iteration) + ".txt";

        // Ouvrir le fichier pour écrire la grille
        std::ofstream file(filename);
        if (!file.is_open()) { // Si le fichier n'a pas pu être ouvert
            std::cerr << "Erreur : Impossible de créer le fichier " << filename << "\n";
            return;
        }

        file << grille; // Écrire la grille dans le fichier
        file.close(); // Fermer le fichier
        std::cout << "Grille sauvegardee dans " << filename << "\n";
    }
    catch (const fs::filesystem_error& e) { // En cas d'erreur lors de la sauvegarde du fichier
        std::cerr << "Erreur lors de la sauvegarde : " << e.what() << "\n";
    }
}

// Retourner le chemin du dossier de sortie
std::string Fichier::getDossierSortie() const {
    return dossierSortie; // Retourner le chemin du dossier de sortie
}
