all: main HashMap HashMapCopy

main: main.o 
	g++ -std=c++17 -Wall -o main main.o
	
	
main.o: main.cpp HashMap.h
	g++ -std=c++17 -Wall -c main.cpp 

HashMap: HashMap.o
	g++ -std=c++17 -Wall -o HashMap HashMap.o

HashMap.o: HashMap.cpp HashMap.h 
	g++ -std=c++17 -Wall -c HashMap.cpp

HashMapCopy: HashMapCopy.o
	g++ -std=c++17 -Wall -o HashMapCopy HashMapCopy.o

HashMapCopy.o: HashMapCopy.cpp
	g++ -std=c++17 -Wall -c HashMapCopy.cpp 

clean:
	rm *.o
	rm main HashMap HashMapCopy

