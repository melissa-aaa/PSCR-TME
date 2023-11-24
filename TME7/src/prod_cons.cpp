#include "Stack.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>

#define M 12
#define N 10


using namespace std;
using namespace pr;

void producteur (Stack<char> * s) {
	char c ;

	cout << "Ecrivez un caractère svp :)" << endl;
	while (true) { // cin.get(c)
		s->push('c');
	}
	cout << "la 2" << endl;
}

void consomateur (Stack<char> * s) {
	while (true) {
		char c = s->pop();
		cout << "consommateur " << c << endl ;
	}
	cout << "la 4" << endl;
}

int main () {
	cout << "here" << endl;
	int fd = shm_open("/monstack", O_RDWR | O_EXCL, 0666);
	perror("shm_open "); 
	if(ftruncate(fd, sizeof(Stack<char>))) {
		perror("ftruncate");
	}
	void* ptr = mmap(NULL, sizeof(Stack<char>), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	Stack<char> * s = new (ptr) Stack<char>();

	int i = 0;
	while(i < N){
		if (fork()==0) {
			producteur(s);
			return 0;
		}
		i++;
	}
	i = 0;
	while(i < M){
		if (fork()==0) {
			consomateur(s);
			return 0;
		}
		i++;
	}
    for(i = 0; i< N+M; i++){
		wait(0);
	}

	s->~Stack();
	munmap(ptr, sizeof(Stack<char>));
	return 0;
}

