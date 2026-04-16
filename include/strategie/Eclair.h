#pragma once
#include <string>

#include "StrategiePaiement.h"

class Eclair: public StrategiePaiement {
public:
	double calculerTotal(double sousTotal) const override;

	std::string obtenirDescription() const override;

private:

	static constexpr double FRAIS_ECLAIR = 1.5;
};