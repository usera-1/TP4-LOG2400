#pragma once
#include <string>

#include "StrategiePaiement.h"

class Poly : public StrategiePaiement {
public:

	double calculerTotal(double sousTotal) const override;

	std::string obtenirDescription() const override;

private:

	static constexpr double RABAIS_POLY = 2.0;

};