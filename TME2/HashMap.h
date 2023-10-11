#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <iostream>   
#include <vector>
#include <forward_list>
#include <utility>
#include <string>
#include <functional>
//#include <iterator>

namespace pr {
	using namespace std;

	// TME 3 Question 1 & 2
	/*
	size_t count(iterator begin, iterator end) {
		size_t cpt = 0;
		while (begin != end) {
			cpt++;
			begin++;
		}
		return cpt;
	}

	template<typename T>
	size_t count_if_equal(iterator begin, iterator end, const T& val) {
		size_t cpt = 0;
		while (begin != end) {
			if(*begin == val) {
				cpt++;
			}
			begin++;
		}
		return cpt;
	}
	*/

	template<typename K, typename V>

	class HashMap {
		size_t taille; // Taille de la table de hachage (nombre d'éléments)
		size_t capaciteMax; // nombre d'éléments max de la table de hachage
		std::vector<std::forward_list<std::pair<K,V>>> tabHash; //vecteur de listes chaînées pour stocker les éléments
		//forward_liste est un parcours -> mais consomme moins de mémoire 
		

        // Fonction de hachage basique pour obtenir un index dans le tableau
        size_t hash(const K& key) const {
            //on crée un objet de hashage (fonction standard fournie par C++) 
            return std::hash<K>{}(key) % capaciteMax;
        }

		public : 

		//Constructeur  
		HashMap(size_t capacite) : taille(0), capaciteMax(capacite), tabHash(capacite) {};

		// Fonction pour insérer un élément dans la table de hachage
		bool put(const K& key, const V& value) {
			size_t index = hash(key); //chercher l'index de l'élément avec la fonction de hachage 
			std::forward_list<std::pair<K,V>>& liste = tabHash[index]; // Liste chaînée correspondante à l'index dans la table de hachage
			bool inserer = false;

			if(existe(key)) {
				//parcourt les paires et met à jour la valeur 
				for (std::pair<K,V>& paire : liste){
					if(paire.first == key) {
						paire.second = value;
						inserer = true;
						return inserer;
					}
				}
                return false;
			} else {
				//créer une paire et l'insérer
				std::pair<K,V> newP = make_pair(key,value);
				liste.push_front(newP);
                inserer = true;
                return inserer;
			}
		}

		//vérifier l'existence avec exists() avant d'utilier get
		V get(const K& key) {
			size_t index = hash(key);
			std::forward_list<std::pair<K,V>>& liste = tabHash[index]; // Liste chaînée correspondante à l'index dans la table de hachage


			for(const std::pair<K,V>& paire : liste) {
				if(paire.first == key) {
					return paire.second;
				}
			}

            //cout << "None value found :/" << endl;
            return 0; //aucune valeur n'a été trouvée 
		}
		
		bool existe(const K& key) const {
			size_t index = hash(key); // Chercher l'index de l'élément avec la fonction de hachage
			const std::forward_list<std::pair<K, V>> & liste = tabHash[index]; // Liste chaînée correspondante à l'index dans la table de hachage

			// Parcourir la liste pour vérifier si la clé existe
			for (const std::pair<K, V>& paire : liste) {
				if (paire.first == key) {
					return true; // La clé existe
				}
			}

			return false; // La clé n'existe pas
		}

		// Fonction pour obtenir le nombre d'élément de la table de hachage
		size_t size() const {
			return taille;
		}

        // méthode renvoie une référence  à la liste chaînée à un index donné (sinon jsp comment faire la 8)
        vector<pair<K, V>> getAllPairs() const {
            vector<pair<K, V>> pairs;
            for (const forward_list<pair<K, V>>& list : tabHash) {
                for (const pair<K, V>& pair : list) {
                    pairs.push_back(pair);
                }
            }
            return pairs;
        }
	
		typedef pair<K,V>* iterator;
		class Iterator {
			std::vector<std::forward_list<std::pair<K,V>>> buckets = tabHash;
			int vit = 0;
			iterator lit = buckets[vit].iterator();

			public: 
				iterator& operator++() { 
					lit++;

					if(lit == nullptr) {
						while(lit == nullptr && vit < capaciteMax) {
							vit++;
							lit = buckets[vit].iterator();
						}

						if(vit == capaciteMax && lit == nullptr) {
							return nullptr;
						}
					}

					return lit;
				}

				bool operator!=(const iterator &other) {
					return ((this.vit != other.vit) && (this.lit != other.lit));
				}

				pair<K, V>& operator*() { 
					return *lit;
				}

		};

		iterator begin() {
			return *(tabHash.begin()).begin();
		}

		iterator end() {
			return iterator(nullptr);
		}
		
	};

}


#endif