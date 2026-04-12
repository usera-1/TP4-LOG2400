#pragma once
#include <string>
#include "Yogourt.h"

class YogourtNature: public Yogourt
{
public:
	YogourtNature() = default;

	double obtenirPrix() const override;

	std::string obtenirDescription() const override;
private:
	static constexpr double PRIX = 2.00;
};