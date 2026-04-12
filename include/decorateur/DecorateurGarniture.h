#pragma once
#include "Yogourt.h"

class DecorateurGarniture: public Yogourt
{
public:
	DecorateurGarniture(Yogourt* y): yogourt(y){};

	virtual double obtenirPrix() const = 0;

	virtual std::string obtenirDescription() const = 0;

	virtual ~DecorateurGarniture() = default;

protected:
	Yogourt* yogourt;

};