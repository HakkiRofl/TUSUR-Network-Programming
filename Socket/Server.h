#ifndef  SERVER_H
#define SERVER_H


#include "Socket.h"


class server : public socket {
public:
	server() {};
	~server() {};
	virtual void init(const char* IP = "127.0.0.1");
	void listening();
	void bind_socket();
};


#endif SERVER_H