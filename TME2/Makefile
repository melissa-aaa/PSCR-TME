all: main HashMap

main: main.o 
	g++ -std=c++17 -Wall -o main main.o
	
	
main.o: main.cpp HashMap.h
	g++ -std=c++17 -Wall -c main.cpp 

HashMap: HashMap.o
	g++ -std=c++17 -Wall -o HashMap HashMap.o

HashMap.o: HashMap.cpp HashMap.h 
	g++ -std=c++17 -Wall -c HashMap.cpp 

