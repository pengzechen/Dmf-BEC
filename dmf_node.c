#include "dmf_node.h"
#include "dmf_socket.h"
#include "dmf_node_map.h"

static node_t* g_node;

int node_init(int type) {

    g_node = (node_t *) malloc (sizeof(node_t) );
    if (NULL == g_node) {
        fprintf(stderr, "malloc failed");
    }
    memset(g_node, 0 , sizeof(node_t));

    if (type == 1) {
        set_master(g_node);
    } else if (type == 0) {
        set_slaver(g_node);
    } else {
        fprintf(stderr, "new node unkonwn type\n");
    }

    return 0;
}

void node_set_name(const char* name) {
    strncpy(g_node->name, name, NODE_NAME_MAX_LEN);
}

int  node_serve_addr(char* addr) {
    const char * space = ":";
    char* token = strtok(addr, space);
    
    strncpy(g_node->addr, token, IP_LEN);
    token = strtok(NULL, space);
    g_node->port = atoi(token);
    
    return 0;
}


static void req_res_handler(int acceptFd )
{	
    char* buffer = (char*)malloc(sizeof(node_t));
    memset(buffer, 0, sizeof(node_t));

	int receive_bytes = recv( acceptFd, buffer, sizeof(node_t), 0 );
    
    node_t* node = (node_t*)buffer;

    printf("node name: %s\n", node->name);
    printf("addr: %s, port: %d\n", node->addr, node->port);
    printf("path1: %s, data: %s\n", node->conf[0].path, node->conf[0].data);
    map_insert(node);

	send(acceptFd, "hello", 5, 0); 
}


void *node_listening_process(void* arg) {
    int fd = *( (int*)arg );

    struct sockaddr_in sock_in;
	int sock_in_len = sizeof(sock_in);
    int sAccept;

    while(1) {
		sAccept = accept(fd, (struct sockaddr *)&sock_in, &sock_in_len);
		req_res_handler( sAccept );
	}

}

void *node_connection_process(void* arg) {
    int fd = *( (int*)arg );

    
	char message[512] = {0};
	int recv_len;
	int send_len;
        send_len = send(fd, (char*)g_node, sizeof(node_t), 0);
        printf("node size: %ld, send legth: %d\n", sizeof(node_t), send_len);
        recv_len = recv(fd, message, sizeof(message) - 1, 0);
        printf("Receive message length: %d\nData:\n %s\n",recv_len, message);
    close(fd);
}

void node_config_push(char* path, char* rule) {
    strcpy(g_node->conf[0].path, path);
    strcpy(g_node->conf[0].data, rule);        
}

// 启动本节点
int node_start(char* ip, int port) {
    
    int* pfd = (int*)malloc(sizeof(int));
    pthread_t roundCheck;

    
    printf("node start: ");
    if (is_master(g_node)) {

        printf("node type : master\n");
        if ((*pfd = sock_listening(g_node->port)) < 0) {
            fprintf(stderr, "start failed\n");
            return -1;
        }

        printf("node name %s fd: %d\n", g_node->name, *pfd);
	    pthread_create(&roundCheck, NULL, node_listening_process, (void*)pfd);
        
    } else {

        printf("node type : slaver\n");
        if ((*pfd = sock_connection(ip, port)) < 0) {
            fprintf(stderr, "start failed\n");
            return -1;
        }

        printf("node name %s fd: %d\n", g_node->name, *pfd);
	    pthread_create(&roundCheck, NULL, node_connection_process, (void*)pfd);
    }

}