#include "Banque.h"
#include <ostream>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;
using namespace pr;

void work(Banque b){
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
const int NB_COMPTES = 1000;
const int SOLDEINITIAL = 1234;
int main () {
	vector<thread> threads;
	Banque banque(NB_COMPTES, SOLDEINITIAL);

	for(int i=0; i<NB_THREAD; i++) {
		threads.push_back(thread(work, banque));
	}


	for (auto & t : threads) {
		t.join();
	}

	cout << "tout est fini !" << endl;

	// TODO : tester solde = NB_THREAD * JP
	return 0;
}
