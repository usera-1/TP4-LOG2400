#pragma once

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
    virtual std::string obtenirNom() const {return "";}
};


