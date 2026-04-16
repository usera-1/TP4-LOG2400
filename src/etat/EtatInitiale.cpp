#include "../../include/etat/EtatInitiale.h"
#include "../../include/application/Application.h"
#include "../../include/etat/EtatPreparation.h"
#include <iostream>

#include "etat/EtatPreparation.h"

using namespace std;

void EtatInitiale::ajouterYogourt(Application& app) {
    cout << "[Etat Initial] Ajout d'un yogourt..." << endl;
    // Si tu n'as pas d'autre classe d'état prête,
    // commente la ligne changerEtat pour l'instant.
    // app.changerEtat(make_unique<EtatSuivant>());
}

std::string EtatInitiale::obtenirNom() const {
    return "Initiale";
}

void EtatInitiale::terminer(Application& app) {
    std::cout << "La commande doit être preparee avant d'etre terminee.\n";
}

void EtatInitiale::preparer(Application& app) {
    if (app.obtenirListeYogourts().empty()) {
        std::cout << "Impossible de preparer sans yogourt" << std::endl;

    }
    else {
        std::cout << "Preparation en cours...\n";

        app.changerEtat(std::make_unique<EtatPreparation>());
    }

}