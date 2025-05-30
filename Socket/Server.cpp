#include "Server.h"


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "RUSSIAN");
	try
	{
		switch (argc) {
		case 1:
		{
			#ifdef _DEBUG
			std::cout << "Case 1\n";
			#endif
			server server;
			server.init();
			server.get_info();
			server.listening();
			server.KlimovTest(server.get_clients()[0]);
			system("pause");
			break;
		}
		case 2:
		{
			#ifdef _DEBUG
			std::cout << "Case 2\n";
			#endif
			server server;
			server.init(argv[1]);
			server.get_info();
			server.listening();
			server.KlimovTest(server.get_clients()[0]);
			system("pause");
			break;
		}
		case 3:
			#ifdef _DEBUG
			std::cout << "Case 3\n";
			#endif
			server server;
			server.setup(AF_INET, SOCK_STREAM, 0, atoi(argv[2]));
			server.init(argv[1]);
			server.get_info();
			server.listening();
			server.KlimovTest(server.get_clients()[0]);
			system("pause");
			break;
		}
	}
	catch (socketException const& ex)
	{
		std::cout << "������\n";
		std::cout << ex.what() << "\n";
		system("pause");
	}
}



server::~server() { // ��������� ����������� ��� �������� � ������� ������ � ���
	for (clientSock c : clients) {
		closesocket(c.clientConnection);
	}
	clients.clear();
}


void server::listening() {
	!listen(this->Sock, SOMAXCONN) ?
		std::cout << "������������� ����!\n" << std::endl :
		throw(socketException::socketException(failed_connection, WSAGetLastError()));

	clientSock client;

	int clientInfo_size = sizeof(client.clientSockAddrInfo);
	client.clientConnection = accept(Sock,
		(sockaddr*)&client.clientSockAddrInfo, &clientInfo_size);

	if (client.clientConnection == INVALID_SOCKET) {
		closesocket(client.clientConnection);
		throw(socketException::socketException(client_connection_error));
	}
	else {
		std::cout << "������ ���������!" << std::endl;
		get_info(client.clientSockAddrInfo);
		clients.push_back(client);
	}
}


void server::init(const char* IP) {
	socket::init(IP);
	bind_socket();
}


void server::bind_socket() {
	//���������� �� IP-������ � �����, � �������� ���� ��������� �����
	// ��������� �� ���������, ���������� ���������
	// ������ ���������
	bind(this->Sock, (sockaddr*)&SockAddrInfo, sizeof(this->SockAddrInfo)) ?
		throw(socketException::socketException(bind_error, WSAGetLastError())) :
		std::cout << "�������� ������ ������������ �������\n";
}


void server::recv(std::string &recvBuff, clientSock Sock) {
	recvBuff.clear(); // �������
	char buffer[BUFFER_SIZE];
	ZeroMemory(buffer, sizeof(buffer)); // �������
	short packet_size = 0;
	packet_size = ::recv(Sock.clientConnection, buffer, sizeof(buffer), 0);
	#ifdef _DEBUG
	std::cout << "PACKAGE: " << packet_size << std::endl;
	#endif
	// ������������ recv() �������, ���� �� ������ ���������
	if (packet_size == SOCKET_ERROR) {
		throw(socketException::socketException(recv_error, WSAGetLastError()));
	}
	else {
		recvBuff = buffer;
	}
}


void server::send(std::string &sendBuff, clientSock Sock) {
	short packet_size = 0;
	packet_size = ::send(Sock.clientConnection, sendBuff.c_str(), sizeof(char) * sendBuff.size(), 0);
	#ifdef _DEBUG
	std::cout << "PACKAGE: " << packet_size << std::endl;
	std::cout << "\nsendBuff: " << sendBuff << std::endl;
	#endif
	if (packet_size == SOCKET_ERROR) {
		throw(socketException::socketException(recv_error, WSAGetLastError()));
	}
}


std::vector<clientSock> server::get_clients() {
	return clients;
}


//���������� class Klimov
std::string server::get_choice(const std::vector<std::string>& options) {
	std::string buffer;
	for (size_t i = 0; i < options.size(); ++i) {
		buffer.append(std::to_string(i + 1));
		buffer.append(". ");
		buffer.append(options[i]);
		buffer.append("\n");
	}	
	buffer.append("�������� (1-");
	buffer.append(std::to_string(options.size()));
	buffer.append("): ");
	return buffer;
}


void server::KlimovTest(clientSock Sock) {
	std::string message;
	std::string buffer = "=== ���� ������� ===\n"
							"=== ���� ===\n";
	buffer.append(get_choice(goals));
	send(buffer, clients[0]);
	recv(message, Sock);
	goal = static_cast<Goal>(stoi(message));
	message.clear();
	buffer.clear();

	buffer = "=== ������ ������������ ===\n";
	buffer.append(get_choice(subjects));
	send(buffer, Sock);
	recv(message, Sock);
	subject = static_cast<Subject>(stoi(message));
	message.clear();
	buffer.clear();

	buffer = "=== ����������� ===\n";
	buffer.append(get_choice(tools));
	send(buffer, Sock);
	recv(message, Sock);
	tool = static_cast<Tools>(stoi(message));
	message.clear();
	buffer.clear();

	buffer = "=== ������� ===\n";
	buffer.append(get_choice(conditions));
	send(buffer, Sock);
	recv(message, Sock);
	cond = static_cast<Conditions>(stoi(message));
	message.clear();
	buffer.clear();

	buffer = get_result();
	send(buffer, Sock);
}