#include "Yogourt.h"
#include <iostream>
using namespace std;


class Yogourt{

    public:

        void ajouterGarniture(const string& garniture){
            garnitures.push_back(garniture);
        }

        void retirerGarniture(){
            if(!garnitures.empty()){
                garnitures.pop_back();
            }
        }

        void afficherGarniture(){
            for(auto& garniture: garnitures){
                cout << garniture << " ";
            }
            cout << endl;
        }

    







    private:
        vector<string> garnitures;
        

};