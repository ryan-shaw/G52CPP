#include "Network.h"

int Network::InitNetwork(){
	printf("Initializing the network\n");
	recvbufflen = DEFAULT_BUFLEN;
	// Init WinSock
	iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if(iResult != 0){
		// Something went wrong with Winsock
		printf("WSAStartup failed with error %d\n", iResult);
		return 0;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

	// Resolve the server address
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if(iResult != 0){
		printf("getaddrinfo failed with error %d\n", iResult);
		WSACleanup();
		return 0;
	}

	// Create a socket for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if(ListenSocket == INVALID_SOCKET){
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 0;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if(iResult == SOCKET_ERROR){
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 0;
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 0;
    }

	// Accept client connection
	ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 0;
    }

	// Probably will not need this!
	closesocket(ListenSocket);

	Packet packet;
	do {
		//printf("Waiting on recv");
		int size;
		size = recv(ClientSocket, (char*)&packet, sizeof(packet), 0);
		printf("Bytes received: %d\n", size);
		printf("Data: %d %d\n",packet.x, packet.y);
	}while(iResult > 0);
	return 1;
};