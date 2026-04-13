#include "Yogourt.h"
#include <iostream>
using namespace std;


// RECEPTEUR



    void Yogourt::ajouterGarniture(const string& garniture){
        garnitures.push_back(garniture);
        cout << "Garniture ajoutée: " << garniture << endl;
    }

    void Yogourt::retirerGarniture(const std::string& garniture) {
        for (int i = garnitures.size() - 1; i >= 0; --i) {
            if (garnitures[i] == garniture) {
                 garnitures.erase(garnitures.begin() + i);
                break;
                }
            }
        cout << "Garniture retirée: " << garniture << endl;
    }


    void Yogourt::afficherGarniture(){
        for(auto& garniture: garnitures){
            cout << garniture << " ";
        }
        cout << endl;
    }