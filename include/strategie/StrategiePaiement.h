#pragma once

class StrategiePaiement {

public:
	virtual double calculerTotal(double sousTotal) const = 0;

	virtual std::string obtenirDescription() const = 0;

	virtual ~StrategiePaiement() = default;
};