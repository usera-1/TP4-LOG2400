#include "../../include/etat/EtatInitiale.h"
#include "../../include/application/Application.h"
#include <iostream>

using namespace std;

void EtatInitiale::ajouterYogourt(Application& app) {
    cout << "[Etat Initial] Ajout d'un yogourt..." << endl;
    // Si tu n'as pas d'autre classe d'état prête,
    // commente la ligne changerEtat pour l'instant.
    // app.changerEtat(make_unique<EtatSuivant>());
}