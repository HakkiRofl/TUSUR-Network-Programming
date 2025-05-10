// Socket_client.h : ���������� ���� ��� ����������� ��������� ���������� ������
// ��� ���������� ����� ��� ����������� �������.

#ifndef Socket_client
#define Socket_client

#include <iostream>
#include <string>
#include <assert.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

enum error { init_failed = 1, invalid_socket = 2, IP_translate = 3,
	sub_IP_out_range = 4, num_IP_out_range = 5, failed_connection = 6
};


struct settings
{
	int af = AF_INET;
	int type = SOCK_STREAM;
	int protocol = 0;
	int port = 1111;
};


class client {
private:
	WSAData WSADataStruct;
	in_addr IPtoNum;
	sockaddr_in SockAddrInfo; //�������� ���� IP-����c/���� � ������
	SOCKET ClientSock;
	settings sets;
	int valid_ip(std::string IP);
public:
	void init(const char* IP = "127.0.0.1");
	void connecting();
	//client(const char* IP = "127.0.0.1");
	client() {};
	~client();
	void get_client_info();
	void setup(int af = AF_INET, int type = SOCK_STREAM, int protocol = 0, int port = 1111);
};


class ClientException : public std::exception {
private:
	friend class client;
	std::string errors;
	ClientException() {};
	ClientException(enum error error, int WSA_error = 0) {
		switch (error)
		{
		case init_failed:
			errors = ("������ �������������: �� ������� ���������� DLL!\n" + std::to_string(WSA_error));
			break;
		case invalid_socket:
			errors = ("������ ������������� ������:\n" + std::to_string(WSA_error));
			break;
		case IP_translate:
			errors = ("IP_translate" + WSA_error);
			break;
		case sub_IP_out_range:
			errors = ("ip-����� ������ ���� � ������� N.N.N.N!\n");
			break;
		case num_IP_out_range:
			errors = ("ip-����� ������ ����� ����� � ��������� �� 0 �� 255!\n");
			break;
		case failed_connection:
			errors = ("�� ������� ������������ � �������!\n" + std::to_string(WSA_error));
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







// TODO: ���������� ����� ������ �� �������������� ���������, ����������� ��� ���������.
