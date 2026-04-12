#pragma once
#include <string>
#include "DecorateurGarniture.h"

class Granola : public DecorateurGarniture
{
public:

	Granola(Yogourt* y);

	double obtenirPrix() const override;

	std::string obtenirDescription() const override;

private:
	static constexpr double PRIX = 0.80;
};