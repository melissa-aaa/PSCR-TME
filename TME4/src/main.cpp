#include <ostream>
#include <iostream>
#include <thread>
#include <vector>

#include "Banque.h"

using namespace std;
using namespace pr;

void work(Banque& b){
	for (int k=0; k<1000; k++) {
		int i = ::rand() %  b.size();
		int j = ::rand() %  b.size();
		int m = (::rand() %  100) + 1;

		b.transfert(i,j,m);

		int t = (::rand() %  20);
		std::this_thread::sleep_for (std::chrono::milliseconds(t));	
	}
	cout << "j'ai fini'!" << endl;
}

const int NB_THREAD = 10;
const int NB_COMPTES = 10;
const int SOLDEINITIAL = 1234;
int main (int argc, const char* argv[]) {
	vector<thread> threads;
	Banque banque(NB_COMPTES, SOLDEINITIAL);

	for(auto & c : banque.getComptes()) {
		cout << "Solde du compte : " << c.getSolde() << endl;
	}

	for(int i=0; i<NB_THREAD; i++) {
		threads.emplace_back(thread(work, ref(banque)));
	}

	for (auto & t : threads) {
		t.join();
	}

	for(auto & c : banque.getComptes()) {
		cout << "Solde du compte : " << c.getSolde() << endl;
	}

	cout << "tout est fini !" << endl;

	// TODO : tester solde = NB_THREAD * JP
	return 0;
}
