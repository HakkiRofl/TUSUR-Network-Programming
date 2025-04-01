#ifndef  SERVER_H
#define SERVER_H


#include "Socket.h"
#include "../Klimov/Klimov.h"
#include <vector>


struct clientSock {
	sockaddr_in clientSockAddrInfo;
	SOCKET clientConnection;
};



class server : public socket, public Klimov {
private:
	std::vector<clientSock> clients;
public:
	server() {};
	~server();
	virtual void init(const char* IP = "127.0.0.1");
	void listening();
	void bind_socket();
	std::vector<clientSock> get_clients();
	virtual void recv(std::string &recvBuff, clientSock Sock);
	virtual void send(std::string &sendBuff, clientSock Sock);
	std::string get_choice(const std::vector<std::string>& options);
	void KlimovTest(clientSock Sock);
};


#endif SERVER_H