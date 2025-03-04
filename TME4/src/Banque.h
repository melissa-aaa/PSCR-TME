#pragma once

#include <vector>
#include <mutex>

#include "Compte.h"

using namespace std;

namespace pr {

	class Banque {
		mutable mutex m;
		typedef std::vector<Compte> comptes_t;
		comptes_t comptes;
	public :
		Banque (size_t ncomptes, size_t solde) : comptes (ncomptes, Compte(solde)){
		}
		void transfert(size_t deb, size_t cred, unsigned int val) ;
		size_t size() const ;
		
		vector<Compte> getComptes() {
			return comptes; 
		}
		bool comptabiliser (int attendu);

		
	};

}
