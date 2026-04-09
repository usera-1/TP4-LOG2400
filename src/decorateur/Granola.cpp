#include "decorateur/Granola.h"

Granola::Granola(Yogourt* y): DecorateurGarniture(y){}

double Granola::obtenirPrix() const {
	return yogourt->obtenirPrix() + PRIX;
}
