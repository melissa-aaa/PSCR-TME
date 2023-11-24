all : pipe pc

pipe.o : pipe.cpp
	g++ -std=c++1y -Wall -c pipe.o pipe.cpp -pthread -lrt 

pipe : pipe.o
	g++ -std=c++1y -Wall -o pipe pipe.o

pc.o : prod_cons.cpp
	g++ -std=c++1y -Wall -c pc.o prod_cons.cpp -pthread -lrt

pc : prod_cons.o
	g++ -std=c++1y -Wall -o pc prod_cons.o -pthread -lrt
