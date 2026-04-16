#include <iostream>
#include <iomanip>
#include "../../include/application/Application.h"
#include "../../include/etat/EtatCommande.h"
#include "../../include/etat/EtatInitiale.h"
#include "../include/ui/ConsoleColors.h"
#include "../include/decorateur/YogourtGrec.h"
#include "../include/decorateur/YogourtNature.h"
#include "../include/decorateur/Chocolat.h"
#include "../include/decorateur/Miel.h"
#include "../include/decorateur/Granola.h"
#include "../include/decorateur/Fruits.h"
#include "../../include/commandes/AjouterGarnitureCommand.h"
#include "../../include/strategie/Prevente.h"
#include "../../include/strategie/Poly.h"
#include "../../include/strategie/Eclair.h"
#include "../../include/strategie/StrategiePaiement.h"

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
std::vector<Yogourt *> Application::obtenirListeYogourts() {
    return listeYogourts_;
}

double Application::calculerSousTotal() const {
    double total = 0.0;
    for (auto* yogourt : listeYogourts_) {
        if (yogourt != nullptr) {
            total += yogourt->obtenirPrix();
        }
    }
    return total;
}

bool Application::changementStrategiePaiement(const std::string &type) {
    if ( type == "prev" ) {
        modePaiement_ = new Prevente();
    }
    else if ( type == "poly") {
        modePaiement_ = new Poly();
    }
    else if ( type == "eclair") {
        modePaiement_ = new Eclair();
    }
    else {
        cout << "Mode de paiement invalide" << endl;
        return false;
    }
    nomModePaiement_= modePaiement_->obtenirDescription();
    return true;
}

void Application::afficherEtatCommandes() {
    cout << "\nPhase: " << etatActuel_->obtenirNom() << endl;

    if (listeYogourts_.empty()) {
        cout << "Yogourts: aucun\n" << "Sous-total commande: 0.00 CAD"<< endl;
    }
    else {
        std::cout << std::fixed << std::setprecision(2);

        for (int i = 0; i < listeYogourts_.size(); i++) {

            cout << "Yogourts #" << i + 1;

            if (i == yogourtActif_) {
                cout << " (actif)";
            }

            cout << ": " << listeYogourts_[i]->obtenirDescription() << " | Prix: " << listeYogourts_[i]->obtenirPrix()
            << " CAD"<< endl;

        }
        cout << "Sous-total commande: " << calculerSousTotal() <<" CAD"<< endl;
    }

    if (modePaiement_ == nullptr) {
        cout << "Paiement: Aucune | "<< ConsoleColor::yellow << "choisir un mode de paiement" << ConsoleColor::reset <<
        " | " << ConsoleColor::red << "non payable" << ConsoleColor::reset << endl;
    }
    else {
        double sousTotal = calculerSousTotal();
        double total = modePaiement_->calculerTotal(sousTotal);

        cout << fixed << setprecision(2);

        cout << "Paiement: " << modePaiement_->obtenirDescription() << " | Total projete: " << total << " CAD ";

        if ( etatActuel_->obtenirNom() == "Terminee") {
            cout << ConsoleColor::blue<< " | payable" << ConsoleColor::reset << endl;
        }
        else {
            cout << ConsoleColor::red << " | non payable" << ConsoleColor::reset << endl;
        }

    }

}

void Application::traiterCommandes(const string &commande) {
    if (commande == "s") {
        stock_.afficherStockActuel();
    }

    else if (commande == "u") {
        if (etatActuel_->obtenirNom() == "Initiale") {
            invocateur_.annuler();
        }
        else if (etatActuel_->obtenirNom() == "Preparation") {
            cout << "Commande en préparation: annulation verrouillee\n";
        }
        else if (etatActuel_->obtenirNom() == "Terminee") {
            cout << "Commande terminee: annulation impossible.\n";
        }

    }
    else if (commande == "r") {
        invocateur_.retablir();

    }
    else if (commande == "sub") {
        string nom, ingredient;

        cin >> ingredient;

        auto nouvelAbonne = make_unique<Abonne>();
        stock_.abonner(ingredient, nouvelAbonne.get());
        abonnes_.push_back(std::move(nouvelAbonne));

        cout << ConsoleColor::cyan <<"[Abonnement] " << ConsoleColor::reset<<
           "Notifications actives pour '" << ingredient << "'." << endl;
    }
    else if (commande == "subs") {
        cout << ConsoleColor::blue << "Abonnements actifs: \n" << ConsoleColor::reset;
        stock_.afficherAbonnements();

    }
    else if (commande == "unsub") {
        string ingredient;
        cin >> ingredient;

        for (auto& abonne: abonnes_) {
            stock_.desabonner(ingredient, abonne.get());
        }
        cout << ConsoleColor::cyan <<"[Abonnement] "<< ConsoleColor::reset <<
            "Desabonne de " << ingredient << "." << endl;
    }


    else if (commande == "p") {
        etatActuel_->preparer(*this);
    }
    else if (commande == "t") {
        if (etatActuel_->obtenirNom() == "Terminee") {
            cout << "Commande deja terminee.\n";
            return;
        }
        etatActuel_->terminer(*this);
    }

    else if (commande == "c") {
        std::string typeYogourt;
        std::cin >> typeYogourt;

        if (etatActuel_->obtenirNom() == "Terminee") {
            cout << "Commande terminee: impossible de modifier le yogourt.\n";
            return;
        }

        if (listeYogourts_.size() >= NB_YOGOURT_MAX) {
            cout << "Un maximum de 2 yogourts par commande est permis" << endl;
            return;
        }

        if (stock_.retirerDuStock(typeYogourt) == false) return;

        if (typeYogourt == "grec") {
            listeYogourts_.push_back(new YogourtGrec());
        }
        else if (typeYogourt == "nature") {
            listeYogourts_.push_back(new YogourtNature());
        }
        else {
            cout << "Type yogourt invalide" << endl;
        }

        yogourtActif_ = listeYogourts_.size() - 1;

        cout << "Yogourt " << typeYogourt << " selectionne." << endl;

    }
    else if ( commande == "sel") {
        int index;
        std::cin >> index;

        if (listeYogourts_.empty()) {
            cout << "Aucun yogourt actif\n";
            return;
        }

        if (index < 1 || index > listeYogourts_.size()) {
            cout << "Selection invalide\n";
            return;
        }
        if (index == 1 && listeYogourts_.size() < NB_YOGOURT_MAX) {
            cout << "Seulement un yogourt est actif\n";
        }

        yogourtActif_ = index - 1;
    }
    else if ( commande == "f") {

        bool selectionGarnituresTermine = false;
        if (yogourtActif_ == -1) {
            cout << "Selectionnez un yogourt en premier" << endl;
            return;
        }

        while (!selectionGarnituresTermine) {

            cout << ConsoleColor::blue << "\nMenu Garnitures\n" << ConsoleColor::reset <<
                "Yogourt actif: #" << yogourtActif_ + 1<< endl;

            stock_.afficherGarnitures();

            cout << ConsoleColor::magenta << "Choix garnitures: " << ConsoleColor::reset;

            string garniture;
            std::cin >> garniture;

            string nom;

            if (garniture == "1") nom = "fruits";
            else if (garniture == "2") nom = "granola";
            else if (garniture == "3") nom = "miel";
            else if (garniture == "4") nom = "chocolat";
            else if (garniture == "q") {
                cout << ConsoleColor::blue << "Retour au menu principal" << ConsoleColor::reset << endl;
                selectionGarnituresTermine = true;
                return;
            }
            else {
                cout << "Choix invalide\n";
                return;
            }

            if (!stock_.retirerDuStock(nom)) {
                continue;
            }

            Yogourt* ancien = listeYogourts_[yogourtActif_];
            Yogourt* nouveau = nullptr;

            if (nom == "fruits")        nouveau = new Fruits(ancien);
            else if (nom == "granola")  nouveau = new Granola(ancien);
            else if (nom == "miel")     nouveau = new Miel(ancien);
            else if (nom == "chocolat") nouveau = new Chocolat(ancien);

            auto cmd = make_shared<AjouterGarnitureCommand>(
            listeYogourts_, yogourtActif_, nouveau, stock_, nom);
            invocateur_.executer(cmd);

            cout << "Garniture " << nom << " ajoutee.\n";
        }

    }
    else if (commande == "h") {
        afficherCommandes();
    }

    else if (commande == "q") {
        cout << ConsoleColor::blue
                 << "Retour au menu principal.\n"
                 << ConsoleColor::reset;
    }

    else if (commande == "cls" || commande == "clear") {
        system("clear");
    }

    else if ( commande == "mode") {
        string type;
        std::cin >> type;

        if (!changementStrategiePaiement(type)) return;

        cout << ConsoleColor::blue <<  "Mode de paiement actif: " << nomModePaiement_  << ConsoleColor::reset << endl;
    }

    else if ( commande == "pay") {

        string type;

        if (cin.peek() != '\n') {
            cin >> type;
            if (!changementStrategiePaiement(type)) return;
        }


        if (etatActuel_->obtenirNom() != "Terminee") {
            cout << ConsoleColor::red << "Paiement refuse: etat Terminee requis (etat actuel: "
            << etatActuel_->obtenirNom() << ")."
            << ConsoleColor::reset << endl;
        }
        else if (modePaiement_ == nullptr) {
            cout << "Aucun mode de paiement selectionnee" << endl;
        }
        else {
            etatActuel_->payer(*this);

            estPaiementTerminee_ = true;

            double sousTotal = calculerSousTotal();
            double total = modePaiement_->calculerTotal(sousTotal);

            cout << ConsoleColor::cyan << "Paiement accepte ( " << modePaiement_->obtenirDescription()
            << ") | Montant: "<< fixed << setprecision(2) << total
            << " CAD\n"<< "Merci pour votre achat. A bientot!\n" << ConsoleColor::reset << endl;
        }


    }

    else if ( commande == "total") {
        double sousTotal = calculerSousTotal();

        cout << fixed << setprecision(2);

        cout << ConsoleColor::blue <<"Sous-total: " << sousTotal <<" CAD" <<endl;

        if ( modePaiement_ == nullptr) {
            cout << "Choisir un mode de paiement" << endl;
        }
        else {
            double total = modePaiement_->calculerTotal(sousTotal);

            cout << "Total avec " << modePaiement_->obtenirDescription() <<": " << total
            <<" CAD"<< ConsoleColor::reset <<endl;
        }
    }
    else {
        cout << "Commande invalide , commande h pour voir toutes les commandes possibles.\n";
    }

}

void Application::afficherCommandes() {
    cout << left;
    cout << ConsoleColor::cyan <<"Bienvenue sur TonYogourt" << ConsoleColor::reset << endl;
    cout << ConsoleColor::blue <<"Commandes:" << ConsoleColor::reset << endl;
    cout << setw(30) << "	c nature|grec" << "→  Ajouter un yogourt (max 2)" << endl;
    cout << setw(30) << "	sel 1|2" << "→  Selectionner le yogourt actif" << endl;
    cout << setw(30) << "	f" << "→  Ouvrir menu garnitures du yogourt actif" << endl;
    cout << setw(30) << "	u" << "→  Annuler derniere garniture du yogourt actif" << endl;
    cout << setw(30) << "	r" << "→  Refaire derniere garniture du yogourt actif" << endl;
    cout << setw(30) << "	p" << "→  Preparer la commande" << endl;
    cout << setw(30) << "	t" << "→  Terminer la commande" << endl;
    cout << setw(30) << "	mode prev|eclair|poly " << "→  Changer le mode paiement" << endl;
    cout << setw(30) << "	pay" << "→  Finaliser paiement (etat Terminee requis)" << endl;
    cout << setw(30) << "	pay prev|eclair|poly " << "→  Alias mode + payer" << endl;
    cout << setw(30) << "	total" << "→  Afficher sous-total et total projete" << endl;
    cout << setw(30) << "	sub article" << "→  S'abonner au notifications d'un article" << endl;
    cout << setw(30) << "	unsub article" << "→  Se desabonner d'un article" << endl;
    cout << setw(30) << "	subs" << "→  Afficher abonnements actifs" << endl;
    cout << setw(30) << "	clear|cls" << "→  Nettoyer ecran" << endl;
    cout << setw(30) << "	s"<<"→  Afficher stocks" << endl;
    cout << setw(30) << "	h"<<"→  Aide" << endl;
    cout << setw(30) << "	q"<<"→  Quitter" << endl;
}

