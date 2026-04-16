#include "../../include/commandes/CommandManager.h"
#include <iostream>
#include <list>
using namespace std;
//EXECUTEUR


    void Invocateur::executer(CmdPtr commande) {
        commande->executer();
        commandesFaites.push_back(commande);
        commandesAnnulees.clear();
    }


    void Invocateur::annuler(){
        if (!commandesFaites.empty()){
            CmdPtr commande = commandesFaites.back();
            commandesFaites.pop_back();
            commande->annuler();
            commandesAnnulees.push_back(commande);
            cout << "Derniere garniture annulee.\n";
            return;
        }      
        cout << "Aucune garniture a annuler." << endl;
    }


    void Invocateur::retablir(){
        if(!commandesAnnulees.empty()){
            CmdPtr cmd = commandesAnnulees.back();
            commandesAnnulees.pop_back();
            cmd->executer();
            commandesFaites.push_back(cmd);
            cout << "Garniture retablie.\n";
            return;
        }
        cout << "Rien à rétablir." << endl;
    }



