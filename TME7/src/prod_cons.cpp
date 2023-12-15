#include "Stack.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <signal.h>

#define M 6 // les consommateurs
#define N 3 // les producteurs


using namespace std;
using namespace pr;



void producteur (Stack<char> * s) {
	char c ;

	//cout << "Ecrivez un caractère svp :)" << endl;
	while (cin.get(c)) { // cin.get(c)
		//sleep(1);
		s->push(c);
	}
}



void consomateur (Stack<char> * s) {
	while (true) {
		char c = s->pop();
		cout << "je consomme " << c << endl ;
	}
}



// handler de CTRL+C
void handler(int sig) {
	printf("J'ai reçu CTRL+C, libération des ressources puis exit\n");
}



int main () {

	// on crée un segment de mémoire partagée
	int fd;
	if((fd = shm_open("lestack", O_RDWR | O_CREAT | O_EXCL, 0666)) == -1) {
		perror("shm_open "); 
	}
	if(ftruncate(fd, sizeof(Stack<char>))) {
		perror("ftruncate ");
	}
	void* ptr = mmap(NULL, sizeof(Stack<char>), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	Stack<char> * s = new (ptr) Stack<char>();


	// on crée les producteurs
	int i = 0;
	while(i < N){
		if (fork()==0) {
			producteur(s);
			return 0;
		}
		i++;
	}

	// on crée les consommateurs
	i = 0;
	while(i < M){
		if (fork()==0) {
			consomateur(s);
			return 0;
		}
		i++;
	}


	// handler de CTRL+C
    sigset_t set;
    sigemptyset(&set);
    struct sigaction act;
    act.sa_handler = handler;
    act.sa_mask = set;
    act.sa_flags = 0;
    sigaction(SIGINT, &act, NULL);

	// on attend CTRL+C
    sigset_t set2;
    sigfillset(&set2);
    sigdelset(&set2, SIGINT);
	sigsuspend(&set2);

	// on attend la terminaison de tout le monde
    for(i = 0; i< N+M; i++){
		wait(0);
	}

	// on libère les ressources
	s->~Stack();
	munmap(ptr, sizeof(Stack<char>));
	shm_unlink("lestack");


	return EXIT_SUCCESS;
}

