#include "../../include/stock/Stock.h"
#include "../../include/ui/ConsoleColors.h"
#include <iostream>

using namespace std;

Stock::Stock() {
    stock_["nature"] = 3;
    stock_["grec"] = 1;
    stock_["fruits"] = 5;
    stock_["granola"] = 4;
    stock_["miel"] = 4;
    stock_["chocolat"] = 1;
}

void Stock::afficherAbonnements() {

    if (abonnements_.empty()) {
        std::cout<< " - aucun " << endl;
    }

    for (const auto& [arcticle, liste]: abonnements_) {
        if (!liste.empty()) {
            std::cout << " - "<< arcticle << endl;
        }
    }
}


void Stock::abonner(const string& article, IObservateur* obs) {
    abonnements_[article].push_back(obs);
}

void Stock::desabonner(const string& article, IObservateur* obs) {
    if (abonnements_.count(article)) {
        auto& liste = abonnements_[article];
        for (auto it = liste.begin(); it != liste.end(); ++it) {
            if (*it == obs) {
                liste.erase(it);
                break;
            }
        }
    }
}

void Stock::notifier(const string& article) {
    if (abonnements_.count(article)) {
        for (auto* obs : abonnements_[article]) {
            obs->miseAJour(article);
        }
    }
}


void Stock::notifierRetourArticle(const string& article) {
    if (abonnements_.count(article)) {
        for (auto* obs : abonnements_[article]) {
            std::cout << ConsoleColor::cyan <<"[Notif Abonne] '"
            << ConsoleColor::reset<< article << "' est de retour en stock." << std::endl;
        }
    }
}

void Stock::afficherStockInitial() {
    for (auto const& [ingredient, valeur] : stock_) {
        cout << ConsoleColor::blue << "[Stock] " << ConsoleColor::reset <<
             ingredient << " : 0 → " << valeur << endl;
    }
}

void Stock::afficherStockActuel() {
    cout << ConsoleColor::blue << "Stocks actuels: " << ConsoleColor::reset << endl;
    for (auto const& [ingredient, valeur] : stock_) {
        cout << " " << ingredient << " : " << valeur << endl;
    }
}

void Stock::afficherGarnitures() {
    cout << "   1 → fruits (" << stock_.at("fruits") << " en stock)\n";
    cout << "   2 → granola (" << stock_.at("granola") << " en stock)\n";
    cout << "   3 → miel (" << stock_.at("miel") << " en stock)\n";
    cout << "   4 → chocolat (" << stock_.at("chocolat") << " en stock)\n";
    cout << "   q → retour menu principal\n";
}

void Stock::ajouterAuStock(const string& ingredient) {
    // stock_[ingredient]++;
    if (stock_[ingredient] == 0) {
        notifierRetourArticle(ingredient);
    }

    cout << ConsoleColor::blue << "[Stock] " << ConsoleColor::reset
       << ingredient << " : "<< stock_[ingredient]<< " -> "  << ++stock_[ingredient]<< endl;
}

bool Stock::retirerDuStock(const string &ingredient) {
    auto it = stock_.find(ingredient);
    if (it == stock_.end()) {
        cout << "Ingredient inexistant" << endl;
        return false;
    }

    if (it->second <= 0) {
        cout << "Stock insuffisant pour '" << ingredient <<"'" << endl;
        notifier(ingredient);
        return false;
    }

    cout << ConsoleColor::blue << "[Stock] " << ConsoleColor::reset <<
         ingredient << " : " << it->second << " → " << it->second - 1 << endl;

    it->second--;

    if (it->second == 0) {
        notifier(ingredient);
    }

    return true;
}

bool Stock::estDisponible(const string& ingredient) const {
    auto it = stock_.find(ingredient);

    if (it == stock_.end()) {
        return false;
    }

    return it->second > 0;
}