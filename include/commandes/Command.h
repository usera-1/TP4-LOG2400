
#pragma once 


class CommandeAbs {
public:
    virtual ~CommandeAbs() = default;
    virtual void executer() = 0;
    virtual void annuler() = 0;
};