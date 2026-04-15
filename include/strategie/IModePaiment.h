//
// Created by massylia aggoun on 2026-04-15.
//

#ifndef TONYOGOURT_IMODEPAIMENT_H
#define TONYOGOURT_IMODEPAIMENT_H

class IModePaiement {
public:
    virtual double calculerTotal(double sousTotal) const = 0;
    virtual std::string obtenirDescription() const = 0;
    virtual ~IModePaiement() = default;
};

// include/strategie/Prevente.h
class Prevente : public IModePaiement {
public:
    double calculerTotal(double s) const override { return s * 0.90; }
    std::string obtenirDescription() const override { return "Prevente (-10%)"; }
};

// ModePoly donne -2.00$
class ModePoly : public IModePaiement {
public:
    double calculerTotal(double s) const override { return s - 2.00; }
    std::string obtenirDescription() const override { return "Coupon Poly (-2.00)"; }
};
#endif //TONYOGOURT_IMODEPAIMENT_H
