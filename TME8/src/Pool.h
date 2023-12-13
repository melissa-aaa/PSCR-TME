#ifndef SRC_POOL_H_
#define SRC_POOL_H_

#include "Queue.h"
#include "Job.h"
#include <vector>
#include <thread>

namespace pr {
	//fonction exécutée par chaque thread de la pool 
	void poolWorker(Queue<Job> * queue) {
		while (true) {
			// récupère un travail depuis la file d'attente
			Job * j = queue->pop();

			
			if (j == nullptr) {
				// Si le job est nullptr la file est vide => thread doit terminer
            
				return;
			}

			j->run(); //éxécute le job 
			delete j;
		}
	}

class Pool {

	Queue<Job> queue; //file d'attente des jobs à exécuter
	std::vector<std::thread> threads; //vecteur de threads dans la pool
public:
	Pool(int qsize) : queue(qsize) {}

	void start (int nbthread) {
		threads.reserve(nbthread); //réserve  l'espace pour les threads dans le vecteur
		for (int i=0 ; i < nbthread ; i++) {
			threads.emplace_back(poolWorker, &queue); // fait exécuter poolWorker sur le job de la Queue dans le vecteur des threads 
		}
	}
	
	void stop() {
		queue.setBlocking(false); //file d'attente en mode non bloquant
		for (auto & t : threads) {
			t.join(); //attend fin de chaque thread de la pool
		}
		threads.clear(); //vide le vecteur de thread 
	}
	~Pool() {
		stop(); //arrête proprement la pool 
	}
	void addJob (Job * job) {
		queue.push(job);
	}
};

} /* namespace pr */

#endif /* SRC_POOL_H_ */
