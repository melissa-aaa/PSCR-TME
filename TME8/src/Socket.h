#ifndef SRC_SOCKET_H_
#define SRC_SOCKET_H_

#include <netinet/ip.h>
#include <string>
#include <cstring>
#include <iosfwd>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

using namespace std;

namespace pr {

class Socket {
	int fd;

public :
	Socket():fd(-1){}
	Socket(int fd):fd(fd){}

	// tente de se connecter à l'hôte fourni
	void connect(const std::string & host, int port){
		struct addrinfo hints;
		memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
        hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
        hints.ai_flags = 0;
        hints.ai_protocol = 0;          /* Any protocol */
		struct addrinfo* res; 

		int s = getaddrinfo(host, to_string(port), hints, &res);

		if (s != 0) {
            fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
            exit(EXIT_FAILURE);
        }

		fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if(!fd) {
			perror("socket");
			exit(-1);
		}
		connect(fd, res->ai_addr, res->ai_addrlen);
		freeaddrinfo(res);

	}
	

	bool isOpen() const {return fd != -1;}
	int getFD() { return fd ;}

	void close(){
		shutdown(fd);
		::close(fd);

	}
};

std::ostream & operator<< (std::ostream & os, struct sockaddr_in * addr);

}

#endif /* SRC_SOCKET_H_ */
