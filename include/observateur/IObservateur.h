#pragma once
#include <string>
#include <iostream>

class IObservateur {
public:
    virtual void miseAJour(const std::string& article) = 0;
    virtual std::string obtenirNom() const = 0;
    virtual ~IObservateur() = default;
};

class Abonne : public IObservateur {
private:
    std::string nom_;
public:
    Abonne(const std::string& nom) : nom_(nom) {}
    
    void miseAJour(const std::string& article) override {
        // Utilisation de std::endl et std::cout pour éviter les erreurs de namespace
        std::cout << "\n[Notif Abonne] Bonjour " << nom_ 
                  << ", rupture de stock detectee pour '" << article << "'." << std::endl;
    }
    
    std::string obtenirNom() const override { return nom_; }
};