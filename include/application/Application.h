#pragma once
#include <vector>
#include <string>
#include <memory>
#include "../decorateur/Yogourt.h"
#include "../commandes/CommandManager.h"
#include "../stock/Stock.h"
#include "../observateur/IObservateur.h"

class EtatCommande;
class IModePaiement;

class Application
{
public:
	Application();
	~Application();

	static void afficherCommandes();
	void traiterCommandes(const std::string& commande);
	void afficherEtatCommandes();

	// Pour l'observateur
	Stock& obtenirStock() { return stock_; }

	// Fonctions de calcul
	double calculerSousTotal() const;

	void changerEtat(std::unique_ptr<EtatCommande> nouvelEtat);
	void setModePaiement(IModePaiement* mode);

private:
	static const int NB_YOGOURT_MAX = 2;
	Stock stock_;
	std::vector<Yogourt*> listeYogourts_;
	int yogourtActif_ = -1;
	Invocateur invocateur_;

	// Utilisation de unique_ptr pour la gestion automatique de la mémoire
	std::unique_ptr<EtatCommande> etatActuel_;
	IModePaiement* modePaiement_;

	// Vecteur pour garder les abonnés en vie
	std::vector<std::unique_ptr<IObservateur>> abonnes_;
};