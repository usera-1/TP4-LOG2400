#pragma once
#include "DecorateurGarniture.h"

class Fruits : public DecorateurGarniture
{
public:
	Fruits(Yogourt* y);

	double obtenirPrix() const override;
private:
	static constexpr double PRIX = 1.00;
};