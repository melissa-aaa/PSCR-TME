all : pipe prod_cons

pipe : pipe.o
	g++ -std=c++1y -Wall -o pipe pipe.o -pthread 

pipe.o : pipe.cpp
	g++ -std=c++1y -Wall -c pipe.cpp -pthread  


prod_cons.o : prod_cons.cpp Stack.h
	g++ -std=c++1y -Wall -c prod_cons.cpp -pthread 

prod_cons : prod_cons.o Stack.h
	g++ -std=c++1y -Wall -o prod_cons prod_cons.o -pthread 


serveur.o : serveur.cpp
	g++ -std=c++1y -Wall -c serveur.cpp -pthread 


clean :
	rm -f *.o pipe prod_cons
