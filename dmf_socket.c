
#include "dmf_socket.h"


int sock_listening(int port){
    

    int sListen;
    struct sockaddr_in ser;
    sListen = socket(AF_INET, SOCK_STREAM, 0);
    ser.sin_family = AF_INET; 
    ser.sin_port = htons(port); 
    ser.sin_addr.s_addr = htonl(INADDR_ANY); 
    if( bind(sListen, (struct sockaddr*)&ser, sizeof(ser) ) < 0) {
		return -1;
	}
    if( listen(sListen,5) != 0) {
		return -1;
	}
    return sListen;
}


int sock_connection(char* ip, int port) {
    int hSocket;
	struct sockaddr_in servAddr;


	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (hSocket == -1)                  
        return -1;

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(ip);
	servAddr.sin_port = htons(port);
	if(connect(hSocket, (struct sockaddr*) &servAddr, sizeof(servAddr)) == -1) 
        return -1;

    return hSocket;
}