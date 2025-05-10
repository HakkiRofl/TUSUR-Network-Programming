#include "Client.h"


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
			client client;
			client.init();
			client.get_info();
			client.connecting();

			std::string message;
			while (1) {
				std::string answer;
				client.recv(message);
				std::cout << message;
				if (!(message.find("ÐÅÇÓËÜÒÀÒÛ") == std::string::npos))
					break;
				std::cin >> answer;
				client.send(answer);	
			}

			system("pause");
			break;
		}
		case 2:
		{
			#ifdef _DEBUG
			std::cout << "Case 2\n";
			#endif
			client client;
			client.init(argv[1]);
			client.get_info();
			client.connecting();

			std::string message;
			while (1) {
				std::string answer;
				client.recv(message);
				std::cout << message;
				if (!(message.find("ÐÅÇÓËÜÒÀÒÛ") == std::string::npos))
					break;
				std::cin >> answer;
				client.send(answer);
			}

			system("pause");
			break;
		}
		case 3:
			#ifdef _DEBUG
			std::cout << "Case 3\n";
			#endif
			client client;
			client.setup(AF_INET, SOCK_STREAM, 0, atoi(argv[2]));
			client.init(argv[1]);
			client.get_info();
			client.connecting();

			std::string message;
			while (1) {
				std::string answer;
				client.recv(message);
				std::cout << message;
				if (!(message.find("ÐÅÇÓËÜÒÀÒÛ") == std::string::npos))
					break;
				std::cin >> answer;
				client.send(answer);
			}

			system("pause");
			break;
		}
	}
	catch (socketException const& ex)
	{
		std::cout << "Îøèáêà\n";
		std::cout << ex.what() << "\n";
		system("pause");
	}
}


void client::connecting() {
	!connect(Sock, // ñîêåò êëèåíòà
		(sockaddr*)&SockAddrInfo, // àäðåñ ñåðâåðà
		sizeof(SockAddrInfo)) ?
		std::cout << "Âûïîëíåíî ïîäêëþ÷åíèå ê ñåðâåðó\n" << std::endl :
		throw(socketException::socketException(failed_connection, WSAGetLastError()));
}

