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
    //tests de la classe HashMap indépendants iterato
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

    //Quesion 6 

    // Crée une instance de la classe HashMap pour stocker les occurrences des mots
    HashMap<string, int> occurrences(100); 

    ifstream input = ifstream("WarAndPeace.txt");

    if (!input.is_open()) {
        cerr << "Erreur : Impossible d'ouvrir le fichier." << endl;
        return 1;
    }

    //mot lu 
    string word;

    //reg expression qui reconnaît les caractères anormaux 
    regex re( R"([^a-zA-Z])");

    while (input >> word) {
        // élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);

		// word est maintenant "tout propre"
        // Vérifie si le mot existe déjà dans la table de hachage
        if (occurrences.existe(word)) {
            // Le mot existe, donc augmentez le compteur d'occurrences
            int cpt = occurrences.get(word);
            occurrences.put(word, cpt + 1);
        } else {
            // Le mot n'existe pas, donc ajoutez-le avec un compteur initialisé à 1
            occurrences.put(word, 1);
        }
    }

    // Affichez le nombre d'occurrences des mots spécifiques (war, peace, toto)
    cout << "Occurrences de 'war': " << occurrences.get("war") << endl;
    cout << "Occurrences de 'peace': " << occurrences.get("peace") << endl;
    cout << "Occurrences de 'toto': " << occurrences.get("toto") << endl;

    // Vous pouvez également afficher d'autres statistiques comme le nombre total de mots différents, etc.

   //Question 7 
    // Crée un vecteur pour stocker les entrées de la table de hachage
    vector<pair<string, int>> vectorHMap = occurrences.getAllPairs();


    cout << "Taille de vectorHMap : " << vectorHMap.size() << endl;

    // ici, vectorFromHashMap contient une copie des entrées de la table de hachage

   // Question 8 
    sort(vectorHMap.begin(), vectorHMap.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    });

    /* 
    //afficher toutes les entrées du vecteur  

    for (const auto& entry : vectorHMap) {
        cout << "Clé : " << entry.first << ", Valeur : " << entry.second << endl;
    }
    */

    // Afficher les dix mots les plus fréquents
    //cout << "Les dix mots les plus fréquents : " << endl;
    int numMotsAffiches = min(10, static_cast<int>(vectorHMap.size())); // Le nombre réel de mots à afficher
    // for (int i = 0; i < numMotsAffiches; ++i) {
    //     cout << vectorHMap[i].first << " : " << vectorHMap[i].second << " occurrences" << endl;
    // }
    
    // input.close();


    // TME 3

    // Question 5

    HashMap<string, int> tableHash(5000); 
    std::cout << "ici1" << std::endl;

    ifstream i = ifstream("WarAndPeace.txt");
    if (!i.is_open()) {
        cerr << "Erreur : Impossible d'ouvrir le fichier." << endl;
        return 1;
    }

    std::cout << "ici2" << std::endl;

    string w;

    while (i >> w) {
		word = regex_replace ( w, re, "");
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
    for (pair<string, int> pair : tableHash) {
        std::cout << "ici0000" << std::endl; 
        vector.push_back(pair);
    }
    std::cout << "ici4" << std::endl;

    sort(vector.begin(), vector.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    });
    

    
    //afficher toutes les entrées du vecteur  

    for (const auto& entry : vector) {
        cout << "Clé : " << entry.first << ", Valeur : " << entry.second << endl;
    }
    

    std::cout << "ici5" << std::endl;

    // Afficher les dix mots les plus fréquents
    cout << "Les dix mots les plus fréquents : " << endl;
    numMotsAffiches = min(10, static_cast<int>(vector.size())); // Le nombre réel de mots à afficher
    for (int j = 0; j < numMotsAffiches; ++j) {
        cout << vector[j].first << " : " << vector[j].second << " occurrences" << endl;
    std::cout << "ici" << std::endl;
    }
    std::cout << "ici" << std::endl;
    i.close();
    std::cout << "ici" << std::endl;

    return 0;

}