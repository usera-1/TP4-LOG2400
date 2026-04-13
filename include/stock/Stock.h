#pragma once
#include <unordered_map>
#include <string>

class Stock
{

public:
	Stock();
	void afficherStockInitial();
	void afficherStockActuel();
	void afficherGarnitures();
	void ajouterAuStock(const std::string& ingredient);
	bool retirerDuStock(const std::string& ingredient);

private:
	std::unordered_map<std::string, int> stock_;
};