#ifndef _DMF_SOCKET_H_
#define _DMF_SOCKET_H_

#include <WinSock2.h>

int sock_listening(int port);
int sock_connection(char* ip, int port);


#endif  // _DMF_SOCKET_H_