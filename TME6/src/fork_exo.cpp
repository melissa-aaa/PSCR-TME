#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main () {
	const int N = 3;
	std::cout << "main pid=" << getpid() << std::endl;
	int nbfils = 0;
	bool pere = true;

	for (int i=1, j=N; i<=N && j==N && fork()==0 ; i++ ) {
		nbfils = 0;
		pere = false;
		std::cout << " i:j " << i << ":" << j << std::endl;
		for (int k=1; k<=i && j==N ; k++) {
			if ( fork() == 0) {
				j=0;
				std::cout << " k:j " << k << ":" << j << std::endl;
			} else {
				nbfils++;
			}
		}
	}

	if(pere) {
		wait(0);
		exit(0);
	}

	for(int i = 0; i<nbfils; i++) {
		cout << i << endl;
		wait(0);
	}

	return 0;
}
