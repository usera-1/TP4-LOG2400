#include "../../include/application/Application.h"
#include "../../include/etat/EtatCommande.h"
#include "../../include/etat/EtatInitiale.h"
#include <iostream>

using namespace std;

Application::Application() : yogourtActif_(-1), modePaiement_(nullptr) {
    etatActuel_ = make_unique<EtatInitiale>();
}

Application::~Application() = default;

void Application::changerEtat(std::unique_ptr<EtatCommande> nouvelEtat) {
    if (nouvelEtat) {
        etatActuel_ = std::move(nouvelEtat);
    }
}

double Application::calculerSousTotal() const {
    double total = 0.0;
    // On parcourt la liste des yogourts et on appelle calculerPrix() de chacun
    for (auto* yogourt : listeYogourts_) {
        if (yogourt != nullptr) {
            total += yogourt->obtenirPrix();
        }
    }
    return total;
}

void Application::traiterCommandes(const string &commande) {
    if (commande == "s") {
        stock_.afficherStockActuel();
    }
    else if (commande == "u") {
        invocateur_.annuler();
    }
    else if (commande == "r") {
        invocateur_.retablir();
    }
    else if (commande == "sub") {
        string nom, ingredient;
        cout << "Nom de l'abonne : "; cin >> nom;
        cout << "Ingredient a surveiller : "; cin >> ingredient;

        auto nouvelAbonne = make_unique<Abonne>(nom);
        stock_.abonner(ingredient, nouvelAbonne.get());
        abonnes_.push_back(std::move(nouvelAbonne));

        cout << "[Systeme] " << nom << " est abonne aux alertes pour '" << ingredient << "'." << endl;
    }
    else if (etatActuel_) {
        if (commande == "c") {
            etatActuel_->ajouterYogourt(*this, "nature");
        }
        else if (commande == "p") {
            etatActuel_->preparer(*this);
        }
        else if (commande == "t") {
            etatActuel_->terminer(*this);
        }
        else if (commande == "pay") {
            etatActuel_->payer(*this);
        }
        else {
            cout << "Commande '" << commande << "' inconnue." << endl;
        }
    }
}

void Application::afficherCommandes() {
    cout << "\n--- MENU ---" << endl;
    cout << "c : Ajouter | sub : S'abonner | s : Stock | p : Preparer | t : Terminer | pay : Payer | u/r : Undo/Redo" << endl;
}

void Application::afficherEtatCommandes() {
    if (etatActuel_) {
        cout << "Etat actuel : " << etatActuel_->obtenirNom() << endl;
        cout << "Sous-total actuel : " << calculerSousTotal() << " $" << endl;
    }
}