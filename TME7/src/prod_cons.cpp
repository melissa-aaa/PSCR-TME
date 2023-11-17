#include "Stack.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>

#define M 12
#define N 10


using namespace std;
using namespace pr;

void producteur (Stack<char> * stack) {
	char c ;
	while (cin.get(c)) {
		stack->push(c);
	}
}

void consomateur (Stack<char> * stack) {
	while (true) {
		char c = stack->pop();
		cout << c << flush ;
	}
}

int main () {
	Stack<char> * s = new Stack<char>();

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

	delete s;
	return 0;
}

