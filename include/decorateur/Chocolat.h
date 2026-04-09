#pragma once
#include "DecorateurGarniture.h"

class Chocolat :public DecorateurGarniture
{
public:
	Chocolat(Yogourt* y);

	double obtenirPrix() const override;
private:
	static constexpr double PRIX = 0.90;
};