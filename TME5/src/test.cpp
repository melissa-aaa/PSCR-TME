#include "Queue.h"
#include "Job.h"
#include "Pool.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <vector>

using namespace pr;
using namespace std;

int main() {
    // création d'une file d'attente 
    Queue<Job*> jobQueue(5);

    // création d'une Pool 
    Pool threadPool(3);
    threadPool.start(3);

    // création et envoi de jobs
    for (int i = 0; i < 5; ++i) {
        jobQueue.push(new Job());
        threadPool.submit(jobQueue.pop());
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));

    // arrêt des threads
    threadPool.stop();

    std::cout << "Finished testing." << std::endl;

    return 0;
}