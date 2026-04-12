#pragma once
#include <string>
#include "DecorateurGarniture.h"

class Miel: public DecorateurGarniture
{
public:
	Miel(Yogourt* y);

	double obtenirPrix() const override;

	std::string obtenirDescription() const override;

private:
	static constexpr double PRIX = 0.60;
};