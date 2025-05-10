#ifndef CLIENT_H
#define CLIENT_H

#include "Socket.h"
#include "../Klimov/Klimov.h"


class client : public socket, public Klimov {
public:
	client() {};
	~client() {};
	void connecting();
};
#endif