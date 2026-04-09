#pragma once
#include "DecorateurGarniture.h"

class Miel: public DecorateurGarniture
{
public:
	Miel(Yogourt* y);

	double obtenirPrix() const override;
private:
	static constexpr double PRIX = 0.60;
};