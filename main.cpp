#include <iostream>
#include <sstream>
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <thread>
#include "Grid.h"
#include "Jeu.h"
#include "Fichier.h"
#include "Rendu.h"

// Génère un nom de dossier unique
std::string genererNomDossier(const std::string& filename) {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm tm;
    localtime_s(&tm, &now_c);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S");
    return std::filesystem::path(filename).stem().string() + "_" + oss.str() + "_out";
}

int main() {
    std::string filename;
    std::cout << "Veuillez indiquer le chemin du fichier d'entree : ";
    std::getline(std::cin, filename);

    Grid grille;
    try {
        grille.loadFromFile(filename);
    }
    catch (...) {
        std::cerr << "Erreur : Impossible de charger le fichier.\n";
        return 1;
    }

    std::string dossierSortie = genererNomDossier(filename);
    Fichier gestionnaireFichier(dossierSortie);
    gestionnaireFichier.creerDossier();

    Jeu jeu(grille, gestionnaireFichier);

    int choixMode, nombreIterations, delayMs;
    std::cout << "Mode d'affichage disponible: \n 1: console \n 2: graphique \nVeuillez choisir le mode de fonctionnement souhaite(1/2): ";
    std::cin >> choixMode;
    std::cout << "Veuillez indiquer le nombre maximale d'iterations : ";
    std::cin >> nombreIterations;
    std::cout << "Veuillez indiquer le delai entre les iterations (millisecondes) : ";
    std::cin >> delayMs;

    if (choixMode == 1) {
        std::cout << "On est en mode console.\nEtat initial :\n";
        jeu.afficherGrille();
        jeu.sauvegarderGrille(0);

        for (int i = 1; i <= nombreIterations; ++i) {
            jeu.prochaineIteration();
            if (jeu.estIdentiqueALaPrecedente()) {
                std::cout << "Arret : état inchange à l'iteration " << i << ".\n";
                break;
            }
            std::cout << "\nGeneration " << i << " :\n";
            jeu.afficherGrille();
            jeu.sauvegarderGrille(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
        }
    }
    else if (choixMode == 2) {
        const int CELL_SIZE = 20;
        Rendu* rendu = new Rendu(grille.getCols() * CELL_SIZE, grille.getRows() * CELL_SIZE, CELL_SIZE);

        for (int i = 1; i <= nombreIterations; ++i) {
            if (!rendu->estOuverte()) break;

            jeu.prochaineIteration();
            if (jeu.estIdentiqueALaPrecedente()) {
                std::cout << "Arrêt : état inchange à l'iteration " << i << ".\n";
                break;
            }
            jeu.sauvegarderGrille(i);
            rendu->dessinerGrille(jeu.getGrid());
            rendu->afficher();
            std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
        }
        delete rendu;
    }
    else {
        std::cerr << "Choix invalide.\n";
        return 1;
    }

    return 0;
}
