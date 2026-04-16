#include "../../include/strategie/Prevente.h"

double Prevente::calculerTotal(double sousTotal) const {
	return sousTotal *(1 - TAUX_REDUCTION);
}

std::string Prevente::obtenirDescription() const {
	return "Prevente (-10%)";
}
