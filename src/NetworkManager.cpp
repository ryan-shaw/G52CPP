#include <Windows.h>
#include <Winsock2.h>

class NetworkManager
{
private:
	WSADATA wsaData;
	WORD version;
public:
	NetworkManager(){
		init();
	}

	bool init(){
		int error;
		version = MAKEWORD(2, 0);
		error = WSAStartup( version, &wsaData );

		if(error != 0)
			return false; // An error occurred
		
		if(LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 0){
			WSACleanup();
			return false;
		}
	}
};