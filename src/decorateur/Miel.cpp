#include "decorateur/Miel.h"

Miel::Miel(Yogourt* y): DecorateurGarniture(y){}

double Miel::obtenirPrix() const {
	return yogourt->obtenirPrix() + PRIX;
}
