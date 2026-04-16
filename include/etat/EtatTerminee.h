#pragma once
#include <string>

#include "EtatCommande.h"

class EtatTerminee : public EtatCommande {
public:
	// On redéfinit seulement ce que cet état peut faire
	void ajouterYogourt(Application& app);
	std::string obtenirNom() const override;
	void terminer(Application &app) override;
};