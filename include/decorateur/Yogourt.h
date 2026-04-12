#pragma once

// -- TODO : Changer le nom de la classe du fichier et puis ajouter toutes les méthodes nécessaires pour cette composante 
// Composante = Patron de conception, classe, etc etc
class Yogourt
{
public:
    Yogourt() = default;

    virtual double obtenirPrix() const = 0;

    virtual std::string obtenirDescription() const = 0;

    virtual ~Yogourt() = default;
};