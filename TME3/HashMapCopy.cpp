#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <string>
#include <unordered_map>
#include "HashMap.h"


int main(){ 
    using namespace pr;
    using namespace std;

    // TME 3 Quesion 7

    // Crée une instance de la classe HashMap pour stocker les occurrences des mots
    unordered_map<string, int> occurrences(5000); 

    ifstream input = ifstream("WarAndPeace.txt");

    if (!input.is_open()) {
        cerr << "Erreur : Impossible d'ouvrir le fichier." << endl;
        return 1;
    }

    string word;
    regex re( R"([^a-zA-Z])");

    while (input >> word) {
		word = regex_replace ( word, re, "");
		transform(word.begin(),word.end(),word.begin(),::tolower);

        auto p = occurrences.insert(make_pair(word, 1));
        if(p.second == false) { //si la clé était déjà présente dans la table
            //cout << p.first->second << endl;
            (p.first->second)++;
        }
    }

    // Affichez le nombre d'occurrences des mots spécifiques (war, peace, toto)
    cout << "Question 7." << endl;
    cout << "Occurrences de 'war': " << occurrences.find("war")->second << endl;
    cout << "Occurrences de 'peace': " << occurrences.find("peace")->second << endl;
    //cout << "Occurrences de 'toto': " << occurrences.find("toto")->second << endl;

    // on recopie les entrées de la table de hash dans un std::vector
    vector<pair<string, int>> vector;
    for (pair<string, int> pair : occurrences ) {
        vector.push_back(pair);
    }

    cout << "Taille de vector : " << vector.size() << endl;

    sort(vector.begin(), vector.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    });

    // Afficher les dix mots les plus fréquents
    cout << "\nLes dix mots les plus frequents : " << endl;
    int numMotsAffiches = min(10, static_cast<int>(vector.size())); // Le nombre réel de mots à afficher
    for (int i = 0; i < numMotsAffiches; ++i) {
        cout << vector[i].first << " : " << vector[i].second << " occurrences" << endl;
    }
    
    input.close();

    // Question 8

    unordered_map<int, forward_list<string>> mapInverse(34562);
    for (pair<string, int> pair : occurrences ) {
        mapInverse[pair.second].push_front(pair.first);
    }

    int n = 34562;
    cout << "Question 8." << endl;
    cout << "Mots ayant " << n << " occurrences : " << endl;
    for(string mot : mapInverse[n]) {
        cout << mot << endl;
    }

    return 0;

}