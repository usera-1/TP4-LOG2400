#pragma once
#include <unordered_map>
#include <string>

class Stock
{

public:
	Stock();
	void afficherStock();
	void afficherGarnitures();
	bool retirerDuStock(const std::string& ingredient);

private:
	std::unordered_map<std::string, int> stock_;
};