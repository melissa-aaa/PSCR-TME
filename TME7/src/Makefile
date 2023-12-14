all : pipe prod_cons



pipe.o : pipe.cpp
	g++ -std=c++1y -Wall -c pipe.o pipe.cpp -pthread -lrt 

pipe : pipe.o
	g++ -std=c++1y -Wall -o pipe pipe.o



prod_cons.o : prod_cons.cpp Stack.h
	g++ -std=c++1y -Wall -c prod_cons.o prod_cons.cpp -pthread -lrt

prod_cons : prod_cons.o Stack.h
	g++ -std=c++1y -Wall -o prod_cons prod_cons.o -pthread -lrt


serveur.o : serveur.cpp
	g++ -std=c++1y -Wall -c serveur.cpp -pthread -lrt


clean :
	rm -f *.o pipe prod_cons
