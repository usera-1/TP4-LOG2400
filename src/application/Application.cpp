#include <iostream>
#include <iomanip>
#include "../include/ui/ConsoleColors.h"
#include "../include/application/Application.h"
#include "../include/decorateur/YogourtGrec.h"
#include "../include/decorateur/YogourtNature.h"
#include "../include/decorateur/Chocolat.h"
#include "../include/decorateur/Miel.h"
#include "../include/decorateur/Granola.h"
#include "../include/decorateur/Fruits.h"

using namespace std;

Stock Application::obtenirStock() {
	return stock_;
}

double Application::calculerSousTotal() const {
	double sousTotal = 0.0;

	for (Yogourt* y: listeYogourts_) {
		if (y != nullptr) {
			sousTotal += y->obtenirPrix();
		}
	}
	return sousTotal;
}

void Application::afficherEtatCommandes() {
	cout << "\nPhase:" << endl;

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
	cout << "Paiement: Aucune | "<< ConsoleColor::yellow << "choisir un mode de paiement" << ConsoleColor::reset <<
		" | " << ConsoleColor::red << "non payable" << ConsoleColor::reset << endl;

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


void Application::traiterCommandes(const std::string &commande) {

	// cout << "\n";
	if (commande == "c") {
		std::string typeYogourt;
		std::cin >> typeYogourt;

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
			cout << "Aucun yogourt disponible\n";
			return;
		}

		if (index < 1 || index > listeYogourts_.size()) {
			cout << "Selection invalide\n";
			return;
		}
		if (index == 2 && listeYogourts_.size() < NB_YOGOURT_MAX) {
			cout << "Seulement un yogourt est actif\n";
		}

		yogourtActif_ = index - 1;
		cout << "yogourt actif = " << yogourtActif_ << endl;  // debug en attendant le reste du code
	}

	else if ( commande == "f") {

		bool selectionGarnituresTermine = false;
		if (yogourtActif_ == -1) {
			cout << "Yogourts: aucun" << endl;
			return;
		}

		while (!selectionGarnituresTermine) {

			cout << ConsoleColor::blue << "\nMenu Garnitures\n" << ConsoleColor::reset <<
				"	Yogourt actif: #" << yogourtActif_ + 1<< endl;

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
				cout << "Stock insuffisant pour la garniture '" << nom << "'" << endl;
				return;
			};

			Yogourt* y = listeYogourts_[yogourtActif_];

			if (nom == "fruits") {
				listeYogourts_[yogourtActif_] = new Fruits(y);
			}
			else if (nom == "granola") {
				listeYogourts_[yogourtActif_] = new Granola(y);
			}
			else if (nom == "miel") {
				listeYogourts_[yogourtActif_] = new Miel(y);
			}
			else if (nom == "chocolat") {
				listeYogourts_[yogourtActif_] = new Chocolat(y);
			}

			cout << "Garniture " << nom << " ajoutee.\n";
		}

	}

	else if (commande == "s") {
		stock_.afficherStockActuel();
	}

	else {
		cout << "Commande invalide\n";
		return;
	}
}

