#ifndef _DMF_SOCKET_H_
#define _DMF_SOCKET_H_

#include <sys/socket.h>
#include <netinet/in.h>         //for addr.sin_addr.s_addr = INADDR_ANY;
#include <sys/time.h>           //for struct timeval
#include <fcntl.h>              //for fcntl()
#include <stdio.h>              //perror
#include <string.h>
#include <arpa/inet.h>       // inet_ntoa

int sock_listening(int port);
int sock_connection(char* ip, int port);


#endif  // _DMF_SOCKET_H_