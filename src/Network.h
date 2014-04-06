#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

class Network{
private:
	WSAData wsaData;
	int iResult;
	SOCKET ListenSocket;
	SOCKET ClientSocket;
	
	struct addrinfo *result;
	struct addrinfo hints;
	
	int iSendResult;
	char recvbuff[DEFAULT_BUFLEN];
	int recvbufflen;
	struct Packet{
		int x;
		int y;
	};
public:
	int InitNetwork();
	void SendData(char*);	
};