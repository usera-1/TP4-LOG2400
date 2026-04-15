#pragma once
#include "EtatCommande.h"

class EtatInitiale : public EtatCommande {
public:
    // On redéfinit seulement ce que cet état peut faire
    void ajouterYogourt(Application& app);
};