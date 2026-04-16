#include "../../include/etat/EtatTerminee.h"

std::string EtatTerminee::obtenirNom() const {
	return"Terminee";
}

void EtatTerminee::terminer(Application& app) {
	std::cout<<"Commande deja terminee."<<std::endl;
}