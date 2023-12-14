all : client serveur server2


client.o : client.cpp Socket.h
	g++ -std=c++1y -Wall -c client.cpp -pthread

client : client.o
	g++ -std=c++1y -Wall -c client.o


server.o : server.cpp ServerSocket.h
	g++ -std=c++1y -Wall -c server.o -pthread

server : server.o
	g++ -std=c++1y -Wall -c server.o


server2.o : server2.cpp ServerSocket.h
	g++ -std=c++1y -Wall -c server2.o -pthread

server2 : server2.o
	g++ -std=c++1y -Wall -c server2.o


clean : 
	rm -fr *.o client server server2

