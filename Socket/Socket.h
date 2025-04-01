#ifndef SOCKET_H
#define SOCKET_H


#include <iostream>
#include <string>
#include <cassert>
#include <WinSock2.h>
#include <WS2tcpip.h>


#define BUFFER_SIZE 1024


enum error {
	init_failed = 1, invalid_socket = 2, IP_translate = 3,
	sub_IP_out_range = 4, num_IP_out_range = 5, failed_connection = 6,
	bind_error = 7, client_connection_error = 8, recv_error = 9, 
	send_error = 10
};


struct settings {
	int af = AF_INET;
	int type = SOCK_STREAM;
	int protocol = 0;
	int port = 1111;
};


class socket {
protected:
	WSAData WSADataStruct;
	sockaddr_in SockAddrInfo; //хранения пары IP-адреc/Порт в сокете
	SOCKET Sock;
	settings sets;
	in_addr IPtoNum;
	int valid_ip(std::string IP);
public:
	socket() {};
	~socket();
	virtual void init(const char* IP = "127.0.0.1");
	void setup(int af = AF_INET, int type = SOCK_STREAM, int protocol = 0, int port = 1111);
	virtual void recv(std::string& recvBuff);
	virtual void send(std::string &sendBuff);
	void get_info();
	void get_info(sockaddr_in& AddrInfo);
};



class socketException : public std::exception {
private:
	std::string errors;
public:
	socketException() {};
	socketException(enum error error, int WSA_error = -1) {
		switch (error)
		{
		case init_failed:
			errors = ("Ошибка инициализации: не удалось подключить DLL!\n" + std::to_string(WSA_error));
			break;
		case invalid_socket:
			errors = ("Ошибка инициализации сокета:\n" + std::to_string(WSA_error));
			break;
		case IP_translate:
			errors = ("IP_translate" + WSA_error);
			break;
		case sub_IP_out_range:
			errors = ("ip-адрес должен быть в формате N.N.N.N!\n");
			break;
		case num_IP_out_range:
			errors = ("ip-адрес должен иметь числа в диапазоне от 0 до 255!\n");
			break;
		case failed_connection:
			errors = ("Подключение не удалось!" + std::to_string(WSA_error));
			break;
		case bind_error:
			errors = ("Ошибка привязки сокета!!\n" + std::to_string(WSA_error));
			break;
		case client_connection_error:
			errors = ("Не удалось установить соединение с клиентом!!\n");
			break;
		case recv_error:
			errors = ("Ошибка приема сообщения!\n") + std::to_string(WSA_error);
			break;
		case send_error:
			errors = ("Ошибка отправки сообщения!\n") + std::to_string(WSA_error);
			break;
		default:
			break;
		}
	}
	virtual const char* what() const noexcept {
		return errors.c_str();
	}
};
#endif