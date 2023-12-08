#pragma once
#include <iostream>
#include <vector>

namespace pr {

class Job {
public:
	virtual void run () = 0;
	virtual ~Job() {};
};
