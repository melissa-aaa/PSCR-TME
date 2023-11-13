#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <iostream>   
#include <vector>
#include <forward_list>
#include <utility>
#include <string>
#include <functional>



namespace pr {
	
	using namespace std;

	template<typename K, typename V>

	class HashMap {
		
		public : 

			//création d'une entrée paire clé,valeur 
			class Entree {
				public:
					K cle;
					V valeur;
					Entree(const K& k, const V& v) : cle(k), valeur(v){}
			};
		
		private : //je sais pas si on peut sauter de public a privée mais faut d'abord dfinir entrée pour les attributs
			typedef vector<forward_list<Entree>> buckets; //référence vers la table buckets
			buckets bucket; // stock les entrées de la table 
			size_t taille; // Taille de la table de hachage (nombre d'éléments)

		public : 	

        	HashMap(size_t capacite) : bucket(capacite), taille(0) {}; //on construit capacite listes vides dans bucket 

			// Fonction pour insérer un élément dans la table de hachage
			bool put(const K& key, const V& value) {
				size_t hash = std::hash<K>()(key);
				size_t index = hash % bucket.size();
				
				//si l'élément existe on augmente sa valeyr
				for(Entree& e : bucket[index]) {
					if(e.cle == key) {
						e.valeur = value;
						return true;
					}
				}
				//on a trouvée aucun élément => insertion 
				taille++;
				bucket[index].emplace_front(key, value);
				return false;
			}

			//vérifier l'existence avec exists() avant d'utilier get
			V* get(const K& key) {
				size_t hash = std::hash<K>()(key);
				size_t index = hash % bucket.size();


				for(Entree& e : bucket[index]) {
					if(e.cle == key) {
						return &e.valeur;
					}
				}

				cout << "Aucune valeur n'a été trouvé (get) :/" << endl;
				return nullptr; //aucune valeur n'a été trouvée 
			}
		
			bool existe(const K& key) const {
				size_t hash = std::hash<K>()(key);
				size_t index = hash % bucket.size();


				for(const Entree& e : bucket[index]) {
					if(e.cle == key) {
						return true;
					}
				}

				return false; //La clé n'existe pas
			}

			// Fonction pour obtenir le nombre d'élément de la table de hachage
			size_t size() const {
				return taille;
			}

			class iterator {	
				typename buckets::iterator pBuckets;
				typename buckets::iterator vit;
				typename forward_list<Entree>::iterator lit; 

				public : 
					//constructeur 
					iterator(typename buckets::iterator& bucket, typename buckets::iterator& vit, typename forward_list<Entree>::iterator& lit): pBuckets(bucket), vit(vit), lit(lit){}


					iterator & operator++(){
						lit++;
						if(lit == vit->end()) { //si on est au bout de la liste
							vit++;
							while (vit != pBuckets && (vit == bucket.end() || vit->empty())) { // si on tombe sur une case vide dans la table de hashage
								++vit;
							}
							if(vit != pBuckets) {//on a trouvé une entrée
								lit = vit->begin();
							}
						}

						return *this; 

					}

					bool operator!=(const iterator &other) const{
						return (vit!=other.vit) || ( vit == pBuckets && lit != other.lit);
					}

					const Entree& operator*() const {
						return *lit;
					}

				};
			
			iterator begin(){
				typename buckets::iterator vit = bucket.begin();

				while(vit != bucket.end() && vit->empty()) {
					vit++;
				}
				if(vit != bucket.end()) { //on a une entrée 
					return iterator(bucket.end(), vit, vit->begin());
				} else {
					return iterator(bucket.end(), bucket.end(), bucket.front().end());
				}

				
			}

			iterator end(){
				return iterator(bucket.end(), bucket.end(), bucket.front().end());
			}

	};

}


#endif

		