#include "decorateur/Fruits.h"

Fruits::Fruits(Yogourt* y): DecorateurGarniture(y) {}

double Fruits::obtenirPrix() const {
	return yogourt->obtenirPrix() + PRIX;
}


