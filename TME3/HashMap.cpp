#include <iostream>
#include <string>
#include <algorithm>
#include "HashMap.h"

using namespace pr;
using namespace std;

int main(){ 

    HashMap<string, int> h(100);
    h.put("test", 1);
    h.put("test2", 2);
    h.put("test3", 1);
    h.put("test4", 4);
    h.put("test5", 1);
   
    vector<HashMap<string,int>::Entree> vect;

    //on copie dans le vecteur 
    for(auto& e: h) {
        vect.push_back(e);
    }

    //on tri tout avec sort 
    sort(vect.begin(), vect.end(), [](const auto& a, const auto& b) {
        return a.valeur > b.valeur;
    });

    //on test les entrées dans le vecteur 
    for(auto& e: vect) {
        cout << "mot : " << e.cle << " nombre : " << e.valeur << endl;
    }



    return 0;

}