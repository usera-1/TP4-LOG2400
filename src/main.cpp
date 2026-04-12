#include <iostream>
#include "../include/application/Application.h"
#include "../include/ui/ConsoleColors.h"
using namespace std;

int main()
{
    Application app;

    app.obtenirStock().afficherStockInitial();

    app.afficherCommandes();

    while (true) {
        app.afficherEtatCommandes();
        cout << ConsoleColor::magenta << "Commande: " << ConsoleColor::reset;
        string cmd;
        cin >> cmd;
        app.traiterCommandes(cmd);
    }
};