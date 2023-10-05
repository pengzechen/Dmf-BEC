#ifndef _NODE_H_
#define _NODE_H_

// typedef void (*ContFun)(int a);
// typedef struct _req_point req_point;
// struct _req_point {
//     char         path[128];
//     ContFun      addr;
// };

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>   
#include <unistd.h>
#include <pthread.h>

#define NODE_NAME_MAX_LEN      64
#define IP_LEN                 32
#define NODE_ID_MAX_LEN        16

#define NODE_MASTER            (1 << 0)



typedef struct _config_s config_t;
struct _config_s {
    char         path[128];
    char         data[512];
};

typedef struct _node_t node_t;
struct _node_t {

    // 1:master 0:slaver
    unsigned int is_master   :1;


    // node's name and name's hash
    char         name[ NODE_NAME_MAX_LEN ];

    // node's address like "127.0.0.1"
    char         addr[ IP_LEN ];
    unsigned int port;

    config_t     conf[10];
};

void        node_set_name(const char* name);
int         node_init(int type);
int         node_serve_addr(char* addr);
int         node_start(char* ip, int port);
void        node_config_push(char* path, char* rule);



static inline void set_master(node_t* n) {
    n->is_master |= NODE_MASTER;
}

static inline void set_slaver(node_t* n) {
    n->is_master &= ~ NODE_MASTER;
}

static inline int is_master(node_t* n) {
    return (n->is_master & NODE_MASTER);
}

#endif
