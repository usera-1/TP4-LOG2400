#include "../../include/etat/EtatPreparation.h"
#include "../../include/etat/EtatTerminee.h"

std::string EtatPreparation::obtenirNom() const {
	return"Preparation";
}

void EtatPreparation::terminer(Application& app) {
	std::cout << "Commande terminee.\n";
	app.changerEtat(std::make_unique<EtatTerminee>());
}
