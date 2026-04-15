#pragma once
#include <string>
#include <vector>
#include <map>
#include "../observateur/IObservateur.h"

class Stock {
private:
	std::map<std::string, int> stock_;
	std::map<std::string, std::vector<IObservateur*>> abonnements_;

public:
	Stock();
	void afficherStockInitial();
	void afficherStockActuel();
	void afficherGarnitures();
	void ajouterAuStock(const std::string& ingredient);
	bool retirerDuStock(const std::string& ingredient);

	// Méthodes du pattern Observateur
	void abonner(const std::string& article, IObservateur* obs);
	void desabonner(const std::string& article, IObservateur* obs);
	void notifier(const std::string& article);
};