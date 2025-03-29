#ifndef CLIENT_H
#define CLIENT_H

#include "Socket.h"


class client : public socket {
public:
	client() {};
	~client() {};
	void connecting();
};



#endif