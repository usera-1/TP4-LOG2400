#include "decorateur/Chocolat.h"

Chocolat::Chocolat(Yogourt* y): DecorateurGarniture(y){};

double Chocolat::obtenirPrix() const {
	return yogourt->obtenirPrix() + PRIX;
}

std::string Chocolat::obtenirDescription() const {
	return yogourt->obtenirDescription() + " + chocolat";
}



