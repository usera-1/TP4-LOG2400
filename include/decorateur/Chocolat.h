#pragma once
#include <string>
#include "DecorateurGarniture.h"

class Chocolat :public DecorateurGarniture
{
public:
	Chocolat(Yogourt* y);

	double obtenirPrix() const override;

	std::string obtenirDescription() const override;


private:
	static constexpr double PRIX = 0.90;
};