#include "../../include/strategie/Eclair.h"

double Eclair::calculerTotal(double sousTotal) const {
	return sousTotal + FRAIS_ECLAIR;
}

std::string Eclair::obtenirDescription() const {
	return "Vente eclair (+1.50)";
}
