#include "Server.h"


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "RUSSIAN");
	try
	{
		switch (argc) {
		case 1:
		{
			std::cout << "Case 1\n";
			server server;
			server.init();
			//server.bind_socket();
			server.get_info();
			server.listening();
			system("pause");
			break;
		}
		case 2:
		{
			std::cout << "Case 2\n";
			server server;
			server.init(argv[1]);
			server.get_info();
			server.listening();
			system("pause");
			break;
		}
		case 3:
			std::cout << "Case 3\n";
			server server;
			server.setup(AF_INET, SOCK_STREAM, 0, atoi(argv[2]));
			server.init(argv[1]);
			server.get_info();
			server.listening();
			system("pause");
			break;
		}
	}
	catch (socketException const& ex)
	{
		std::cout << "Ошибка\n";
		std::cout << ex.what() << "\n";
		system("pause");
	}
}



void server::listening() {
	!listen(this->Sock, SOMAXCONN) ?
		std::cout << "Прослушивание сети!\n" << std::endl :
		throw(socketException::socketException(failed_connection, WSAGetLastError()));

	//system("pause");
	//get_server_info();
	sockaddr_in clientSockAddrInfo;
	int clientInfo_size = sizeof(clientSockAddrInfo);
	SOCKET clientConnection = accept(Sock,
		(sockaddr*)&clientSockAddrInfo, &clientInfo_size);

	if (clientConnection == INVALID_SOCKET) {
		closesocket(clientConnection);
		throw(socketException::socketException(client_connection_error));
	}
	else {
		std::cout << "Клиент подключен!" << std::endl;
		get_info(this->SockAddrInfo);
	}
}


void server::init(const char* IP) {
	socket::init(IP);
	bind_socket();
}

void server::bind_socket() {
	//информацию по IP-адресу и порту, к которому надо привязать сокет
	// указатель на структуру, содержащую детальную
	// размер структуры
	bind(this->Sock, (sockaddr*)&SockAddrInfo, sizeof(this->SockAddrInfo)) ?
		throw(socketException::socketException(bind_error, WSAGetLastError())) :
		std::cout << "Привязка сокета осуществлена успешно\n";
}