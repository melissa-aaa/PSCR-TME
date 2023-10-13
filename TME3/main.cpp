#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>



int main () {
	using namespace std;
	using namespace std::chrono;

	ifstream input = ifstream("WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	//size_t nombre_lu = 0;
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");

	//on crée le vecteur
	std::vector<pair<string,int>> vect;

	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);

		// word est maintenant "tout propre"
		
		//on parcourt le vecteur pour voir si le mot courant est deja dedans
		bool trouve = false;
		for(int i = 0; i<vect.size(); ++i) {
			if(vect[i].first == word) {
				trouve = true;
				vect[i].second++;
				break;
			}
		}
		if (trouve == false){
			vect.push_back(pair(word,1));
		}
		

		//if (nombre_lu % 100 == 0)
			// on affiche un mot "propre" sur 100
			//cout << nombre_lu << ": "<< word << endl;
		//nombre_lu++;
	}
	input.close();

	vect.shrink_to_fit();

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << vect.size() << " words." << endl;
	
	int cpt = 0;
	string war = "war";
	string peace = "peace";
	string toto = "toto";
	for(int i = 0; i<vect.size(); ++i) {
		if(vect[i].first == (war)) {
			cpt++;
			cout << "Le nombre d'occurences de " << vect[i].first << " est " << vect[i].second << endl;
		}

		if(vect[i].first == (peace)) {
			cpt++;
			cout << "Le nombre d'occurences de " << vect[i].first << " est " << vect[i].second << endl;
		}

		if(vect[i].first == (toto)) {
			cpt++;
			cout << "Le nombre d'occurences de " << vect[i].first << " est " << vect[i].second << endl;
		}

		if(cpt == 3) {
			break;
		}
	}
	if(cpt != 3){
		cout << "Le nombre d'occurences des autres mots est 0 !" << endl;
	}
	

    return 0;
}

