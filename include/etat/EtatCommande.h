//
// Created by massylia aggoun on 2026-04-15.
//

#ifndef TONYOGOURT_ETATCOMMANDE_H
#define TONYOGOURT_ETATCOMMANDE_H

#include "application/Application.h"

class EtatCommande {
public:
    virtual ~EtatCommande() = default;
    // On enlève le = 0 et on met des corps vides {}
    virtual void ajouterYogourt(Application& app, const std::string& type) {}
    virtual void ajouterGarniture(Application& app) {}
    virtual void preparer(Application& app) {}
    virtual void terminer(Application& app) {}
    virtual void payer(Application& app) {}
    virtual std::string obtenirNom() const { return "Etat Inconnu"; }
};

#endif //TONYOGOURT_ETATCOMMANDE_H
