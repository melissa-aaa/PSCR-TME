all : fork_exo Combat pseudowait

fork_exo.o : fork_exo.cpp
	g++ -std=c++17 -Wall -c fork_exo.cpp

fork_exo: fork_exo.o
	g++ -std=c++17 -Wall -o fork_exo fork_exo.o


rsleep.o: rsleep.cpp rsleep.h 
	g++ -std=c++17 -Wall -c rsleep.cpp


Combat.o : Combat.cpp rsleep.h
	g++ -std=c++17 -Wall -c Combat.cpp

Combat : Combat.o rsleep.o
	g++ -std=c++17 -Wall -o Combat Combat.o rsleep.o


pseudowait : pseudowait.cpp
	g++ -std=c++17 -Wall -o pseudowait pseudowait.cpp


clean: 
	rm -f *.o fork_exo Combat pseudowait

