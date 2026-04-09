#pragma once
#include "Yogourt.h"

class YogourtNature: public Yogourt
{
public:
	YogourtNature() = default;

	double obtenirPrix() const override;
private:
	static constexpr double PRIX = 2.00;
};