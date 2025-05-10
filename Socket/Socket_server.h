// Socket_server.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#ifndef Socket_server
#define Socket_server


#include <iostream>
#include <string>
#include <assert.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

enum error {
	init_failed = 1, invalid_socket = 2, IP_translate = 3,
	sub_IP_out_range = 4, num_IP_out_range = 5, failed_connection = 6, 
	bind_error = 7, client_connection_error = 8
};


struct settings
{
	int af = AF_INET;
	int type = SOCK_STREAM;
	int protocol = 0;
	int port = 1111;
};


class server
{
private:
	WSAData WSADataStruct;
	in_addr IPtoNum;
	sockaddr_in SockAddrInfo; //хранения пары IP-адреc/Порт в сокете
	SOCKET serverSock;
	settings sets;
	int valid_ip(std::string IP);
public:
	void bind_socket();
	void init(const char* IP = "127.0.0.1");
	void listening();
	//client(const char* IP = "127.0.0.1");
	server() {};
	~server();
	void get_server_info();
	void get_info(sockaddr_in& AddrInfo);
	void setup(int af = AF_INET, int type = SOCK_STREAM, int protocol = 0, int port = 1111);
};


class serverException: public std::exception {
private:
	friend class server;
	std::string errors;
	serverException() {};
	serverException(enum error error, int WSA_error = -1) {
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
			errors = ("Не удалось подключиться к клиенту!\n" + std::to_string(WSA_error));
			break;
		case bind_error:
			errors = ("Ошибка привязки сокета!!\n" + std::to_string(WSA_error));
			break;
		case client_connection_error:
			errors = ("Не удалось установить соединение с клиентом!!\n");
			break;
		default:
			break;
		}
	}
public:
	virtual const char* what() const noexcept {
		return errors.c_str();
	}
};
#endif

// TODO: установите здесь ссылки на дополнительные заголовки, требующиеся для программы.
