// Socket_server.cpp: определ€ет точку входа дл€ приложени€.
//
#include "Socket_client.h"


using enum error; //C++20


//client::client(const char* IP = "127.0.0.1") {
//	init(IP);
//	connecting();
//}


client::~client() {
	//std::cout << "DESTRUCTOR\n";
	WSACleanup();
	closesocket(ClientSock);
}


void client::setup(int af, int type, int protocol, int port) {
	sets.af = af;
	sets.type = type;
	sets.protocol = protocol;
	sets.port = port;
}


int client::valid_ip(std::string IP)
{
	size_t iter = 0;
	char letter = IP[iter];
	size_t split_count = 1;
	std::string splitted_IP[4];
	std::string buffer;
	while (letter != '\0') {
		if (letter != '.')
			buffer += letter;
		iter++;
		letter = IP[iter];
		if (letter == '.') {
			if (split_count < 4) {
				//std::cout << std::atoi(buffer.c_str()) << std::endl;
				//std::cout << split_count << std::endl;
				if (0 <= std::atoi(buffer.c_str()) && 
					std::atoi(buffer.c_str()) <= 255) {
					splitted_IP[split_count] = buffer;
					split_count++;
					buffer.clear();
				}
				else
					throw(ClientException(num_IP_out_range));
			}
			else
				throw(ClientException(sub_IP_out_range));
		}
	}
	if (split_count < 4)
		throw(ClientException(sub_IP_out_range));
	return 0;
}


void client::init(const char* IP)
{

	WORD DLLVersion = MAKEWORD(2, 2);
	int erStat = WSAStartup(DLLVersion, &WSADataStruct);

	// ќператор Ёлвиса примен€ть нежелательно!!
	erStat ?
		throw(ClientException::ClientException(
			init_failed, WSAGetLastError())) :
		std::cout << "WSA DLL успешно подключена\n";

	ClientSock = socket(sets.af, sets.type, sets.protocol);

	ClientSock == INVALID_SOCKET ?
		throw(ClientException::ClientException(invalid_socket,
			WSAGetLastError())) : 
		NULL;

	assert(!valid_ip("255.255.255.255"));

	!valid_ip(IP) ?
		(inet_pton(sets.af, IP, &IPtoNum) <= 0 ?
			throw(ClientException::ClientException(IP_translate)) :
			NULL) :
		NULL;

	ZeroMemory(&SockAddrInfo, sizeof(SockAddrInfo));
	SockAddrInfo.sin_addr = IPtoNum; // IP-адрес в нужном формате
	SockAddrInfo.sin_family = sets.af; // семейство сетевых протоколов
	SockAddrInfo.sin_port = htons(sets.port); // порт
}


void client::connecting()
{
	!connect(ClientSock, // сокет клиента
		(sockaddr*)&SockAddrInfo, // адрес сервера
		sizeof(SockAddrInfo)) ?
		std::cout << "¬ыполнено подключение к серверу\n" << std::endl:
		throw(ClientException::ClientException(failed_connection, WSAGetLastError()));
	//get_client_info();

}


void client::get_client_info()
{
	std::cout << " IP= " << int(SockAddrInfo.sin_addr.S_un.S_un_b.s_b1)
		<< "." << int(SockAddrInfo.sin_addr.S_un.S_un_b.s_b2)
		<< "." << int(SockAddrInfo.sin_addr.S_un.S_un_b.s_b3)
		<< "." << int(SockAddrInfo.sin_addr.S_un.S_un_b.s_b4)
		<< " Port= " << SockAddrInfo.sin_port
		<< " StackFamily= " << SockAddrInfo.sin_family
		<< " sizeof= " << sizeof(SockAddrInfo) << "\n";
}


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
			client.get_client_info();
			client.connecting();
			system("pause");
			break;
		}
		case 2:
		{
			std::cout << "Case 2\n";
			client client;
						client.init(argv[1]);
			client.get_client_info();
			client.connecting();
			system("pause");
			break;
		}
		case 3:
			std::cout << "Case 3\n";
			client client;
			client.setup(AF_INET, SOCK_STREAM, 0, atoi(argv[2]));
			client.init(argv[1]);
			client.get_client_info();
			client.connecting();
			system("pause");
			break;
		}
	}
	catch (ClientException const& ex)
	{
		std::cout << "ќшибка\n";
		std::cout << ex.what() << "\n";
		system("pause");
	}
}

	//system("pause");

	//int erStat = 0; // код ошибки (статуса)
	//WSAData WSADataStruct;
	//WORD DLLVersion = MAKEWORD(2, 2);
	//erStat = WSAStartup(DLLVersion, &WSADataStruct);
	//if (erStat)
	//{
	//	std::cout << "ошибка подключени€ DLL: " << WSAGetLastError() << "\n";
	//	system("pause");
	//	exit(1);
	//}
	//else
	//	std::cout << "WSA DLL успешно подключена " << erStat << "\n";

	//// »нициализаци€ сокета клиента
	//	SOCKET ClientSock = socket(AF_INET, SOCK_STREAM, 0);
	//if (ClientSock == INVALID_SOCKET) {
	//	std::cout << "ошибка инициализации сокета: " << WSAGetLastError() << "\n";
	//	closesocket(ClientSock);
	//	WSACleanup();
	//	system("pause");
	//	exit(1);
	//}
	//else
	//	std::cout << "сокет инициализирован успешно" << "\n";
	////---------------------------------------------------------------------------
	//// задание информации (адреса и порта) сервера (!)
	//// преобразование строки с IP-адресом в числовой формат in_addr
	//in_addr IPtoNum;
	//erStat = inet_pton(AF_INET, "127.0.0.1", &IPtoNum);
	//if (erStat <= 0)
	//{
	//	std::cout << "ошибка перевода IP в специальный числовой формат" << "\n";
	//	system("pause");
	//	exit(1);
	//}
	//// ѕрив€зка сокета к паре IP-адрес/ѕорт сервера (!)
	//sockaddr_in ServSockAddrInfo;
	//ZeroMemory(&ServSockAddrInfo, sizeof(ServSockAddrInfo));
	//ServSockAddrInfo.sin_addr = IPtoNum; // IP-адрес в нужном формате
	//ServSockAddrInfo.sin_family = AF_INET; // семейство сетевых протоколов
	//ServSockAddrInfo.sin_port = htons(1111); // порт
	////---------------------------------------------------------------------------
	//// установление соединени€ с сервером и прив€зка к его IP-адресу/ѕорту
	//erStat = connect(ClientSock, // сокет клиента
	//	(sockaddr*)&ServSockAddrInfo, // адрес сервера
	//	sizeof(ServSockAddrInfo));
	//if (erStat != 0) {
	//	std::cout << "установить соединение с сервером не удалось: ќшибка # "
	//		<< WSAGetLastError() << "\n";
	//	closesocket(ClientSock);
	//	WSACleanup();
	//	system("pause");
	//	exit(1);
	//}
	//else
	//	std::cout << "соединение с сервером установлено\n";
	////---------------------------------------------------------------------------
	//closesocket(ClientSock); // завершение работы клиентского приложени€
	//WSACleanup();

