#ifndef JOB_H
#define JOB_H
#include <iostream>
#include <vector>

namespace pr {

class Job {
public:
	virtual void run () {
        std::cout << "Executing ConcreteJob..." << std::endl;
    }
	virtual ~Job() {};
};

}

#endif