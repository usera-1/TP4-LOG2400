#pragma once
#include <vector>
#include <string>
#include "../decorateur/Yogourt.h"
#include "../stock/Stock.h"

class Application
{
public:
	static void afficherCommandes();
	void traiterCommandes(const std::string& commande);
	void afficherEtatCommandes();
	Stock obtenirStock();
	double calculerSousTotal() const;

private:
	static const int NB_YOGOURT_MAX = 2;
	Stock stock_;
	std::vector<Yogourt*> listeYogourts_;
	int yogourtActif_ = -1;
};
