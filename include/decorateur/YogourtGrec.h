#pragma once
#include <string>
#include "Yogourt.h"

class YogourtGrec: public Yogourt
{
public:
	YogourtGrec() = default;

	double obtenirPrix() const override;

	std::string obtenirDescription() const override;
private:
	static constexpr double PRIX = 2.50;
};