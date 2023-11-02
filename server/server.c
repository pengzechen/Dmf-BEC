#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dmf_node.h"
#include "dmf_node_map.h"

int main() {
    // 初始化此进程的节点为 master 节点
    node_init(1);           
    node_set_name("master");

    // 用来和其他 slaver 节点通信
    char addr[] = "127.0.0.1:8000";   
    node_serve_addr(addr);

    // 启动一个线程处理
    node_start(NULL, 0);          

    int i = 0;
    node_t* node = NULL;
    for(;;) {
        scanf("%d", &i);
        switch(i) {
            case 0:
                show_map();
            break;
            case 1:
                if ( (node = map_get_node("backends22.pzc.com")) != NULL)
                    printf("%s\n", node->name);
            default:
            break;
        }
    }
    return 0;
}