#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <string>
#include "HashMap.h"


int main(){ 
    using namespace pr;
    using namespace std;

    /*
    //tests de la classe HashMap indépendants
    size_t capacite = 10;

    //HashMap<string,int> h(capacite);

    HashMap<string,int> *h = new HashMap<string,int>(capacite);

    for(size_t i = 0; i < capacite*4 ; i++) {
        
        pair<string,int> *p = new pair<string,int>(to_string(i),i);
        h->put(p->first,p->second);
        cout << h->get(to_string(i)) << endl;
    }

    h->put("1", 32);

    cout << "Valeur modifiée : " << h->get("1") << endl;
    */



    // TME 3

    // Question 5

    HashMap<string, int> tableHash(5000);

    ifstream i = ifstream("WarAndPeace.txt");
    if (!i.is_open()) {
        cerr << "Erreur : Impossible d'ouvrir le fichier." << endl;
        return 1;
    }

    string w;
    //reg expression qui reconnaît les caractères anormaux 
    regex re( R"([^a-zA-Z])");

    while (i >> w) {
		w = regex_replace(w, re, "");
		transform(w.begin(),w.end(),w.begin(),::tolower);
        
        if (tableHash.existe(w)) {
            // Le mot existe, donc augmentez le compteur d'occurrences
            int cpt = tableHash.get(w);
            tableHash.put(w, cpt + 1);
        } else {
            // Le mot n'existe pas, donc ajoutez-le avec un compteur initialisé à 1
            tableHash.put(w, 1); 
        }
    }
    std::cout << "ici3" << std::endl;

    // on recopie les entrées de la table de hash dans un std::vector
    vector<pair<string, int>> vector;
    /*
    for (pair<string, int> pair : tableHash) {
        std::cout << "ici0000" << std::endl; 
        //vector.push_back(pair);
    }
    */

    for(auto it = vector.begin(), _end = vector.end(); it!=_end; ++it){
        std::cout << "ici0000" << std::endl; 
        vector.push_back(*it);
    }
    //std::cout << "ici4" << std::endl;

    sort(vector.begin(), vector.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    });
    

    
    //afficher toutes les entrées du vecteur  

    for (const auto& entry : vector) {
        cout << "Clé : " << entry.first << ", Valeur : " << entry.second << endl;
    }
    

    // Afficher les dix mots les plus fréquents
    cout << "Les dix mots les plus frequents : " << endl;
    int numMotsAffiches = min(10, static_cast<int>(vector.size())); // Le nombre réel de mots à afficher
    for (int j = 0; j < numMotsAffiches; ++j) {
        cout << vector[j].first << " : " << vector[j].second << " occurrences" << endl;
    }

    i.close();

    return 0;

}