#ifndef SRC_SERVERSOCKET_H_
#define SRC_SERVERSOCKET_H_

#include <iostream>
#include <ostream>

#include "Socket.h"

using namespace std;

namespace pr {

class ServerSocket {
	int socketfd;

public :
	// Demarre l'ecoute sur le port donne
	ServerSocket(int port){
		fd = socket(AF_INET, SOCK_STREAM, 0);
		if(!fd) {
			perror("fd");
			exit(-1);
		}
		sin.sin_family = AF_INET;
		sin.sin_port = htons(port);
		sin.sin_addr.s_addr = INADDR_ANY;
		if(bind(fd, (struct sockaddr *) &sin, sizeof(sin))) {
			close(fd);
		}

		listen(fd,50);
		sockfd = fd;
	}

	int getFD() { return socketfd;}
	bool isOpen() const {return socketfd != -1;}

	Socket accept(){
		int fd = accept(socketfd, 0,0);
		struct sockaddr_in addr;
		socklen_t len = sizeof(addr);
		if(fd = accept(socketfd, &addr, &len) == -1) {
			perror("accept ");
			exit(-1);
		}

		cout << "Connexion de " << addr << endl;
		return fd;
	}

	void close();
};

} // ns pr
#endif /* SRC_SERVERSOCKET_H_ */
