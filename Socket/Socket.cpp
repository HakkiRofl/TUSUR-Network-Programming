#include "Socket.h"


using enum error; //C++20


socket::~socket() {
	//std::cout << "DESTRUCTOR\n";
	WSACleanup();
	closesocket(Sock);
}


void socket::setup(int af, int type, int protocol, int port) {
	sets.af = af;
	sets.type = type;
	sets.protocol = protocol;
	sets.port = port;
}


int socket::valid_ip(std::string IP)
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
					throw(socketException(num_IP_out_range));
			}
			else
				throw(socketException(sub_IP_out_range));
		}
	}
	if (split_count < 4)
		throw(socketException(sub_IP_out_range));
	return 0;
}


void socket::init(const char* IP)
{

	WORD DLLVersion = MAKEWORD(2, 2);
	int erStat = WSAStartup(DLLVersion, &WSADataStruct);

	// ќператор Ёлвиса примен€ть нежелательно!! 
	if (erStat)
		throw(socketException::socketException(
			init_failed, WSAGetLastError()));


#ifdef _DEBUG
	std::cout << "WSA DLL успешно подключена\n";
#endif

	Sock = ::socket(sets.af, sets.type, sets.protocol);

	Sock == INVALID_SOCKET ?
		throw(socketException::socketException(invalid_socket,
			WSAGetLastError())) :
		NULL;

	assert(!valid_ip("255.255.255.255"));

	!valid_ip(IP) ?
		(inet_pton(sets.af, IP, &IPtoNum) <= 0 ?
			throw(socketException::socketException(IP_translate)) :
			NULL) :
		NULL;

	ZeroMemory(&SockAddrInfo, sizeof(SockAddrInfo));
	SockAddrInfo.sin_addr = IPtoNum; // IP-адрес в нужном формате
	SockAddrInfo.sin_family = sets.af; // семейство сетевых протоколов
	SockAddrInfo.sin_port = htons(sets.port); // порт
}


void socket::recv(char(&recvBuff)[], const short BUFF_SIZE) {
	//ZeroMemory(recvBuff, sizeof(&recvBuff)); // очистка
	char buffer[1024];
	ZeroMemory(buffer, sizeof(buffer));
	short packet_size = 0;
	packet_size = ::recv(Sock, buffer, sizeof(buffer), 0);
	std::cout << "Packet_Size: " << packet_size;
	// подпрограмма recv() ожидает, пока не придет сообщение
	if (packet_size == SOCKET_ERROR) {
		throw(socketException::socketException(recv_error, WSAGetLastError()));
	}
	else {
		std::strncpy(recvBuff, buffer, BUFF_SIZE);
	}
}


void socket::send(char (&sendBuff)[], const short BUFF_SIZE) {
	short packet_size = 0;
	packet_size = ::send(Sock, sendBuff, sizeof(char) * BUFF_SIZE, 0);
	// подпрограмма recv() ожидает, пока не придет сообщение
	if (packet_size == SOCKET_ERROR) {
		throw(socketException::socketException(send_error, WSAGetLastError()));
	}
}


void socket::get_info()
{
	std::cout << " IP= " << int(SockAddrInfo.sin_addr.S_un.S_un_b.s_b1)
		<< "." << int(SockAddrInfo.sin_addr.S_un.S_un_b.s_b2)
		<< "." << int(SockAddrInfo.sin_addr.S_un.S_un_b.s_b3)
		<< "." << int(SockAddrInfo.sin_addr.S_un.S_un_b.s_b4)
		<< " Port= " << SockAddrInfo.sin_port
		<< " StackFamily= " << SockAddrInfo.sin_family
		<< " sizeof= " << sizeof(SockAddrInfo) << "\n";
}


void socket::get_info(sockaddr_in& AddrInfo)
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