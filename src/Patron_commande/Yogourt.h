#include <string>
using namespace std;
#include <vector>

class Yogourt {
public:
    void ajouterGarniture(const string& garniture);
    void retirerGarniture(const string& garniture);
    void afficherGarniture();


private:
    vector<string> garnitures;
};