#include <iostream>
#include "../../include/stock/Stock.h"
#include "../../include/ui/ConsoleColors.h"

Stock::Stock() {
	stock_["nature"] = 3;
	stock_["grec"] = 1;
	stock_["fruits"] = 5;
	stock_["granola"] = 4;
	stock_["miel"] = 4;
	stock_["chocolat"] = 1;
}

void Stock::afficherStockInitial() {
	for (auto& [ingredient,valeur]: stock_) {
		std::cout << ConsoleColor::blue <<"[Stock] " << ConsoleColor::reset <<
			ingredient << " : 0 → " << valeur << std::endl;
	}
}

void Stock::afficherStockActuel() {
	std::cout << ConsoleColor::blue << "Stocks: " << ConsoleColor::reset << std::endl;
	for (auto& [ingredient,valeur]: stock_) {
		std::cout << "	"<<ingredient << " : " << valeur << std::endl;
	}
}


void Stock::afficherGarnitures() {
	std::cout << "	1 → fruits (" << stock_.at("fruits") << " en stock)\n";
	std::cout << "	2 → granola (" << stock_.at("granola") << " en stock)\n";
	std::cout << "	3 → miel (" << stock_.at("miel") << " en stock)\n";
	std::cout << "	4 → chocolat (" << stock_.at("chocolat") << " en stock)\n";
	std::cout << "	q → retour menu principal\n";
}

bool Stock::retirerDuStock(const std::string& ingredient) {

	auto ing = stock_.find(ingredient);
	if (ing == stock_.end()) {
		std::cout << "Ingredient inexistant" << std::endl;
		return false;
	}
	if (ing->second <= 0) {
		std::cout << "Stock insuffisant pour " << ingredient << std::endl;
		return false;
	}

	std::cout << ConsoleColor::blue <<"[Stock] " << ConsoleColor::reset <<
		ingredient << " : " << ing->second << "→" << ing->second - 1 << std::endl;

	ing->second--;

	return true;

}

