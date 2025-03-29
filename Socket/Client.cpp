#include "Client.h"


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "RUSSIAN");
	try
	{
		switch (argc) {
		case 1:
		{
			std::cout << "Case 1\n";
			client client;
			client.init();
			client.get_info();
			client.connecting();
			system("pause");
			break;
		}
		case 2:
		{
			std::cout << "Case 2\n";
			client client;
			client.init(argv[1]);
			client.get_info();
			client.connecting();
			system("pause");
			break;
		}
		case 3:
			std::cout << "Case 3\n";
			client client;
			client.setup(AF_INET, SOCK_STREAM, 0, atoi(argv[2]));
			client.init(argv[1]);
			client.get_info();
			client.connecting();
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


void client::connecting() {
	!connect(Sock, // сокет клиента
		(sockaddr*)&SockAddrInfo, // адрес сервера
		sizeof(SockAddrInfo)) ?
		std::cout << "Выполнено подключение к серверу\n" << std::endl :
		throw(socketException::socketException(failed_connection, WSAGetLastError()));
	//get_client_info();
}