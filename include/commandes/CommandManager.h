#pragma once
#include <list>
#include <memory>
#include "Command.h"



using CmdPtr = std::shared_ptr<CommandeAbs>;

class Invocateur {
public:
    void executer(CmdPtr commande);
    void annuler();
    void retablir();

private:
    std::list<CmdPtr> commandesFaites;
    std::list<CmdPtr> commandesAnnulees;
};