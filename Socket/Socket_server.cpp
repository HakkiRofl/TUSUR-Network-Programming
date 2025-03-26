// Socket_server.cpp: определяет точку входа для приложения.
//

#include "Socket_server.h"


using enum error; //C++20


//server::server(const char* IP = "127.0.0.1") {
//	init(IP);
//	connecting();
//}


server::~server() {
	//std::cout << "DESTRUCTOR\n";
	WSACleanup();
	closesocket(serverSock);
}


void server::setup(int af, int type, int protocol, int port) {
	sets.af = af;
	sets.type = type;
	sets.protocol = protocol;
	sets.port = port;
}


int server::valid_ip(std::string IP)
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
					throw(serverException(num_IP_out_range));
			}
			else
				throw(serverException(sub_IP_out_range));
		}
	}
	if (split_count < 4)
		throw(serverException(sub_IP_out_range));
	return 0;
}


void server::init(const char* IP)
{

	WORD DLLVersion = MAKEWORD(2, 2);
	int erStat = WSAStartup(DLLVersion, &WSADataStruct);

	// Оператор Элвиса применять нежелательно!!
	erStat ?
		throw(serverException::serverException(
			init_failed, WSAGetLastError())) :
		std::cout << "WSA DLL успешно подключена\n";

	serverSock = socket(sets.af, sets.type, sets.protocol);

	serverSock == INVALID_SOCKET ?
		throw(serverException::serverException(invalid_socket,
			WSAGetLastError())) :
		NULL;

	assert(!valid_ip("255.255.255.255"));

	!valid_ip(IP) ?
		(inet_pton(sets.af, IP, &IPtoNum) <= 0 ?
			throw(serverException::serverException(IP_translate)) :
			NULL) :
		NULL;

	ZeroMemory(&SockAddrInfo, sizeof(SockAddrInfo));
	SockAddrInfo.sin_addr = IPtoNum; // IP-адрес в нужном формате
	SockAddrInfo.sin_family = sets.af; // семейство сетевых протоколов
	SockAddrInfo.sin_port = htons(sets.port); // порт
	bind_socket();
}


void server::bind_socket() {
	//информацию по IP-адресу и порту, к которому надо привязать сокет
	// указатель на структуру, содержащую детальную
	// размер структуры
	bind(serverSock, (sockaddr*)&SockAddrInfo, sizeof(SockAddrInfo)) ? 
		throw(serverException::serverException(bind_error, WSAGetLastError())) :
		std::cout << "Привязка сокета осуществлена успешно\n";
}

void server::listening()
{// Снизу исходник, просто продолжить!
	!listen(serverSock, SOMAXCONN) ?
		std::cout << "Прослушивание сети!\n" << std::endl :
		throw(serverException::serverException(failed_connection, WSAGetLastError()));
	
	//system("pause");
	//get_server_info();
	sockaddr_in clientSockAddrInfo;
	int clientInfo_size = sizeof(clientSockAddrInfo);
	SOCKET clientConnection = accept(serverSock,
		(sockaddr*)&clientSockAddrInfo, &clientInfo_size);
	
	if (clientConnection == INVALID_SOCKET) {
		closesocket(clientConnection);
		throw(serverException::serverException(client_connection_error));
	}
	else {
		std::cout << "Клиент подключен!" << std::endl;
		get_info(clientSockAddrInfo);
	}
		

}


void server::get_server_info()
{
	std::cout << " IP= " << int(SockAddrInfo.sin_addr.S_un.S_un_b.s_b1)
		<< "." << int(SockAddrInfo.sin_addr.S_un.S_un_b.s_b2)
		<< "." << int(SockAddrInfo.sin_addr.S_un.S_un_b.s_b3)
		<< "." << int(SockAddrInfo.sin_addr.S_un.S_un_b.s_b4)
		<< " Port= " << SockAddrInfo.sin_port
		<< " StackFamily= " << SockAddrInfo.sin_family
		<< " sizeof= " << sizeof(SockAddrInfo) << "\n";
}
void server::get_info(sockaddr_in &AddrInfo)
{
	std::cout << " Client:" << std::endl;
	std::cout << " IP= " << int(AddrInfo.sin_addr.S_un.S_un_b.s_b1)
		<< "." << int(AddrInfo.sin_addr.S_un.S_un_b.s_b2)
		<< "." << int(AddrInfo.sin_addr.S_un.S_un_b.s_b3)
		<< "." << int(AddrInfo.sin_addr.S_un.S_un_b.s_b4)
		<< " Port= " << AddrInfo.sin_port
		<< " StackFamily= " << AddrInfo.sin_family
		<< " sizeof= " << sizeof(AddrInfo) << "\n";
}
//		SOCKET Sock = socket(AF_INET, SOCK_STREAM, 0);
//		erStat = bind(Sock, // сокет
//			(sockaddr*)&SockAddrInfo, // указатель на структуру, содержащую детальную
//			// информацию по IP-адресу и порту, к которому надо привязать сокет
//			sizeof(SockAddrInfo)); // размер структуры
//		if (erStat != 0) {
//			std::cout << "ошибка привязки сокета # " << WSAGetLastError() << "\n";
//			closesocket(Sock);
//			WSACleanup();
//			system("pause");
//			exit(1);
//		}
//		else
//			std::cout << "привязка сокета осуществлена успешно\n";
//		while (1)
//		{
//			erStat = listen(Sock, SOMAXCONN);
//			if (erStat != 0) {
//				std::cout << "ошибка старта процесса прослушивания сети # "
//					<< WSAGetLastError() << "\n";
//				closesocket(Sock);
//				WSACleanup();
//				system("pause");
//				exit(1);
//			}
//			else
//				std::cout << "прослушивание сети...\n";
//			//-------------------------------------------
//		}
//	}

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
			server.get_server_info();
			server.listening();
			system("pause");
			break;
		}
		case 2:
		{
			std::cout << "Case 2\n";
			server server;
			server.init(argv[1]);
			server.get_server_info();
			server.listening();
			system("pause");
			break;
		}
		case 3:
			std::cout << "Case 3\n";
			server server;
			server.setup(AF_INET, SOCK_STREAM, 0, atoi(argv[2]));
			server.init(argv[1]);
			server.get_server_info();
			server.listening();
			system("pause");
			break;
		}
	}
	catch (serverException const& ex)
	{
		std::cout << "Ошибка\n";
		std::cout << ex.what() << "\n";
		system("pause");
	}
}

//int main()
//{
//	setlocale(LC_ALL, "Rus");
//	//system("pause");
//
//	int erStat = 0; // код ошибки (статуса)
//	WSAData WSADataStruct;
//	WORD DLLVersion = MAKEWORD(2, 2);
//	erStat = WSAStartup(DLLVersion, &WSADataStruct);
//	if (erStat)
//	{
//		std::cout << "ошибка подключения DLL: " << WSAGetLastError() << "\n";
//		system("pause");
//		exit(1);
//	}
//	else
//		std::cout << "WSA DLL успешно подключена " << erStat << "\n";
//
//	SOCKET Sock = socket(AF_INET, SOCK_STREAM, 0); // инициализация сокета
//	if (Sock == INVALID_SOCKET) // проверка
//	{
//		std::cout << "ошибка инициализации сокета: " << WSAGetLastError() << "\n";
//		closesocket(Sock); // закрытие сокета
//		WSACleanup(); // закрытие библиотек WSA
//		system("pause"); // пауза
//		exit(1); // завершение приложения
//	}
//	else
//		std::cout << "сокет инициализирован успешно\n";
//
//	// преобразование строки с IP-адресом в числовой формат in_addr
//	in_addr IPtoNum;
//	erStat = inet_pton(AF_INET, "127.0.0.1", &IPtoNum); // ❹
//	//
//	if (erStat <= 0) // проверка корректности трансформации IP-адреса ❺
//	{
//		std::cout << "ошибка перевода IP в специальный числовой формат\n";
//		system("pause");
//		exit(1);
//	}
//	else
//	{
//		std::cout << "IP-адрес переведен в специальный числовой формат\n";
//		//---------------------------------------------------------------------------
//		// Подготовка структуры для хранения IP-адрес/Порт ❻
//		sockaddr_in SockAddrInfo; // структура для хранения пары IP-адрес/Порт
//		ZeroMemory(&SockAddrInfo, sizeof(SockAddrInfo)); // обнуление блока памяти
//		SockAddrInfo.sin_addr = IPtoNum; // IP-адрес в нужном формате
//		SockAddrInfo.sin_family = AF_INET; // семейство сетевых протоколов
//		SockAddrInfo.sin_port = htons(1111); // порт
//		//----------------------------------------------------------
//		// Визуализация формата хранения IP-адреса ❼
//		std::cout << " IP= " << int(SockAddrInfo.sin_addr.S_un.S_un_b.s_b1)
//			<< "." << int(SockAddrInfo.sin_addr.S_un.S_un_b.s_b2)
//			<< "." << int(SockAddrInfo.sin_addr.S_un.S_un_b.s_b3)
//			<< "." << int(SockAddrInfo.sin_addr.S_un.S_un_b.s_b4)
//			<< " Port= " << SockAddrInfo.sin_port
//			<< " StackFamily= " << SockAddrInfo.sin_family
//			<< " sizeof= " << sizeof(SockAddrInfo) << "\n";
//		SOCKET Sock = socket(AF_INET, SOCK_STREAM, 0);
//		erStat = bind(Sock, // сокет
//			(sockaddr*)&SockAddrInfo, // указатель на структуру, содержащую детальную
//			// информацию по IP-адресу и порту, к которому надо привязать сокет
//			sizeof(SockAddrInfo)); // размер структуры
//		if (erStat != 0) {
//			std::cout << "ошибка привязки сокета # " << WSAGetLastError() << "\n";
//			closesocket(Sock);
//			WSACleanup();
//			system("pause");
//			exit(1);
//		}
//		else
//			std::cout << "привязка сокета осуществлена успешно\n";
//		while (1)
//		{
//			erStat = listen(Sock, SOMAXCONN);
//			if (erStat != 0) {
//				std::cout << "ошибка старта процесса прослушивания сети # "
//					<< WSAGetLastError() << "\n";
//				closesocket(Sock);
//				WSACleanup();
//				system("pause");
//				exit(1);
//			}
//			else
//				std::cout << "прослушивание сети...\n";
//			//-------------------------------------------
//		}
//	}
//}
