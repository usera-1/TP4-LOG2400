#include <iostream>
// #include "pattern1/Pattern1.h"
// #include "pattern2/Pattern2.h"
#include "../include/decorateur/Chocolat.h"
#include "../include/decorateur/Miel.h"
#include "../include/decorateur/Granola.h"
#include "../include/decorateur/Fruits.h"
#include "../include/decorateur/YogourtGrec.h"
#include "../include/decorateur/YogourtNature.h"
#include "../include/stock/Stock.h"
#include "../include/ui/ConsoleColors.h"

const int NB_YOGOURT_MAX = 2;


void afficherCommandes() {
    std::cout << ConsoleColor::cyan <<"Bienvenue sur TonYogourt" << ConsoleColor::reset << std::endl;
    std::cout << ConsoleColor::blue <<"Commandes:" << ConsoleColor::reset << std::endl;
    std::cout << "c nature|grec       →  Ajouter un yogourt (max 2)" << std::endl;
    std::cout << "sel 1|2             →  Selectionner le yogourt actif" << std::endl;
    std::cout << "f                   →  Ouvrir menu garnitures" << std::endl;
    std::cout << "u                   →  Annuler derniere garniture" << std::endl;
    std::cout << "r                   →  Refaire derniere garniture" << std::endl;
    std::cout << "p                   →  Preparer la commande" << std::endl;
    std::cout << "t                   →  Terminer la commande" << std::endl;
    std::cout << "mode prev|eclair    →  Changer mode paiement" << std::endl;
    std::cout << "pay                 →  Finaliser paiement" << std::endl;
    std::cout << "total               →  Afficher total" << std::endl;
    std::cout << "clear|cls           →  Nettoyer ecran" << std::endl;
    std::cout << "s                   →  Afficher stocks" << std::endl;
    std::cout << "h                   →  Aide" << std::endl;
    std::cout << "q                   →  Quitter" << std::endl;
}

void traiterCommandes(std::string& commande,Stock& stock,std::vector<Yogourt*>& listeYogourts, int& actif) {
    if (commande == "c") {
        std::string typeYogourt;
        std::cin >> typeYogourt;

        if (listeYogourts.size() >= NB_YOGOURT_MAX) return; // pas plus de 2 yogurt actifs

        if (stock.retirerDuStock(typeYogourt) == false) return;

        if (typeYogourt == "grec") {
            listeYogourts.push_back(new YogourtGrec());
        }
        else if (typeYogourt == "nature") {
            listeYogourts.push_back(new YogourtNature());
        }
        else {
            std::cout << "Type yogourt invalide" << std::endl;
        }

        actif = listeYogourts.size() - 1;

        std::cout << "Yogourt " << typeYogourt << " selectionne." << std::endl;

    }

    else if ( commande == "sel") {
        int index;
        std::cin >> index;

        actif = index - 1;

        std::cout << "Yogourt #" << index << " selectionne.\n";
    }

    else if ( commande == "f") {
        if (actif == -1) {
            std::cout << "Yogourts: aucun" << std::endl;
        }

        int garniture;
        std::cin >> garniture;

        if (!stock.retirerDuStock(garniture)) {
            return;
        }

        Yogourt* yogourtActif = listeYogourts[actif];

        if (garniture == 1) {
            listeYogourts[actif] = new Chocolat(yogourtActif);
        }
        else if (garniture == 2) {
            listeYogourts[actif] = new Miel(yogourtActif);
        }
        else if (garniture == 3) {
            listeYogourts[actif] = new Granola(yogourtActif);
        }
        else if (garniture == 4) {
            listeYogourts[actif] = new Fruits(yogourtActif);
        }

        std::cout << "Garniture " << garniture << " ajoutee.\n";

    }
}

int main()
{
    std::vector<Yogourt*> yogourts;
    Stock stock;
    int yogourtActif = 1;

    stock.afficherStock();
    afficherCommandes();
    while (true) {
        std:std::string cmd;
        std::cin >> cmd;
        traiterCommandes(cmd,stock,yogourts,yogourtActif);
    }
};