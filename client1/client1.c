#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dmf_node.h"
#include <unistd.h>

int main() {

    // 初始化此进程的节点为  slaver  节点
    node_init(0);           
    node_set_name("backends22.pzc.com");

    // 本节点服务监听端口
    char  addr[] = "127.0.0.1:5001";
    node_serve_addr(addr);     


    node_config_push("/api/add_book", "Uri, Code, Host, User-Agent");
    printf("node config doen.\n");

    // 和master节点通信
    node_start("127.0.0.1", 8000);  


    for(;;) {
        // printf("Main thread\n");
        sleep(3);
    }
    return 0;
}