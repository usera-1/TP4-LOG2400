#include "../../include/strategie/Poly.h"

#include <string>

double Poly::calculerTotal(double sousTotal) const {
	return sousTotal - RABAIS_POLY;
}

std::string Poly::obtenirDescription()const {
	return "Mode poly (-2.00)";
}

