#include "Banque.h"

#include <iostream>
#include <mutex>

using namespace std;

namespace pr {

	void Banque::transfert(size_t deb, size_t cred, unsigned int val) {
		unique_lock<mutex> l(m);
		Compte & debiteur = comptes[deb];
		Compte & crediteur = comptes[cred];
		if (debiteur.debiter(val)) {
			crediteur.crediter(val);
		}
	}
	size_t Banque::size() const {
		unique_lock<mutex> l(m);
		return comptes.size();
	}
	bool comptabiliser (int attendu) const {
			unique_lock<mutex> l(m);
			int bilan = 0;
			int id = 0;
			for(const auto& compte : comptes) {
				if(compte.getSolde() < 0) {
					cout << "Compte "  <<id<< " en négatif = " << compte.getSolde() << endl;

				}
				bilan += compte.getSolde():
				id++
			}
			if (bilan != attendu) {
				cout << "Bilan comptable faux : attendu " << attendu << " obtenu : " << bilan << endl;
			}
			return bilan == attendu;
		}
}
