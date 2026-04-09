#pragma once
#include "Yogourt.h"

class YogourtGrec: public Yogourt
{
public:
	YogourtGrec() = default;

	double obtenirPrix() const override;
private:
	static constexpr double PRIX = 2.50;
};