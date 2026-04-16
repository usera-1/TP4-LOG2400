#pragma once
#include <string>

#include "StrategiePaiement.h"

class Prevente : public StrategiePaiement {
public:

	double calculerTotal(double sousTotal) const override;

	std::string obtenirDescription() const override;

private:

	static constexpr double TAUX_REDUCTION = 0.10;

};