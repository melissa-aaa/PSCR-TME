#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include <string>
#include "exo1.h"

using namespace std;

int main () {

	//Exercice 1.1 ALgorithme 
	vector<string> test;
	test.push_back("Hello1");
	test.push_back("Hello2");
	test.push_back("Hello3");
	test.push_back("Hello4");
	test.push_back("Hello5");

	if(test.size() == pr::count(test.begin(), test.end())){
		cout << "cout fonctionne :)" << endl;
	}

	test.push_back("Hello1");
	if(pr::count_if_equal(test.begin(), test.end(), "Hello1") == 2) {
		cout << "cout_if_equal fonctionne :)" << endl;
	}


	// Exercice 1.2 Itérateurs sur HashMap 
	return 0;
}

