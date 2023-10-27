all : fork_exo


fork_exo: fork_exo.o
	g++ -std=c++17 -Wall -o fork_exo fork_exo.o

rsleep.o: rsleep.cpp rsleep.h 
	g++ -std=c++17 -Wall -o rsleep.o rsleep.cpp


%.o: %.cpp
	g++ -std=c++1y -Wall -c -o $@ $^ 

clean: 
	rm -f *.o fork_exo

