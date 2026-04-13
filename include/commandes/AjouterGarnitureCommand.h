#pragma once
#include "Command.h"
#include "../decorateur/Yogourt.h"
#include "../stock/Stock.h"
#include <vector>
#include <string>

class AjouterGarnitureCommand : public CommandeAbs {
public:
    AjouterGarnitureCommand(std::vector<Yogourt*>& liste, int index, Yogourt* nouvelleGarniture, Stock& stock, const std::string& nom)
        : liste_(liste), index_(index), nouvelleGarniture_(nouvelleGarniture), ancienYogourt_(liste[index]), stock_(stock), nom_(nom) {}

    void executer() override {
        ancienYogourt_ = liste_[index_];
        liste_[index_] = nouvelleGarniture_;
    }

    void annuler() override {
        nouvelleGarniture_ = liste_[index_];
        liste_[index_] = ancienYogourt_;
        stock_.ajouterAuStock(nom_);  
    }

private:
    std::vector<Yogourt*>& liste_;
    int index_;
    Yogourt* nouvelleGarniture_;
    Yogourt* ancienYogourt_;
    Stock& stock_;
    std::string nom_;
};