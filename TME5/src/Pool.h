#ifndef POOL_H
#define POOL_H

#include "Queue.h"
#include "Job.h"
#include <vector>
#include <thread>
#include <iostream>
#include <algorithm>
#include <string>

namespace pr {

class Pool {
	Queue<Job> queue;
	std::vector<std::thread> threads;
public:
	Pool(int qsize) : queue(qsize) {} // constructeur 

	void start(int nbthread) {
		for (int i = 0; i < nbthread; ++i) {
			threads.emplace_back([this]() { //notation lambda entraîne aucune erreur 
				while (true) {
					Job* job = queue.pop();
					if (job == nullptr) {
						// queue est vide donc le thread se termine.
						break;
					}
					job->run();
					delete job; // libérer la mémoire sinon erreur segfault 
				}
			});
		}
	}

	void submit(Job* job) {
		queue.push(job); //ajoute un job à la file d'attente 
	}

	void stop() {
		for (int i = 0; i < threads.size(); ++i) {
			queue.push(nullptr); // thread va s'arrêter car job null 
		}

		// attendre la fin des threads 
		for (auto& thread : threads) {
			thread.join();
		}
	}

	~Pool() {
		stop(); 
	}

};

}

#endif // POOL_H
