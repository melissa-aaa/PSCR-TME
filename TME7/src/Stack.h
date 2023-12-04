#pragma once

#include <cstring> // size_t,memset
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>

using namespace std;

namespace pr {

#define STACKSIZE 5

template<typename T>
class Stack {
	T tab [STACKSIZE];
	size_t sz;
	sem_t mutex, sprod, scons;

public :

	Stack () : sz(0) {
		sem_init(&mutex, 1, 1);
		sem_init(&sprod, 1, STACKSIZE);
		sem_init(&scons, 1, 0);
		memset(tab,0,sizeof tab);
	}

	~Stack() {
		sem_destroy(&mutex);
		sem_destroy(&scons);
		sem_destroy(&sprod);
	}

	T pop () {
		sem_wait(&(scons));
		sem_wait(&(mutex));
		T toret = tab[--sz];
		sem_post(&(mutex));
		sem_post(&(sprod));
		return toret;
	}

	void push(T elt) {
		sem_wait(&(sprod));
		sem_wait(&(mutex));
		tab[sz++] = elt;
		sem_post(&(mutex));
		sem_post(&(scons));
	}
};

}
