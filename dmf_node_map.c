#include "dmf_node_map.h"

hash_node_t g_node_map[ HASH_DEC_LEN ];

static unsigned int BKDRHash(char *str)
{
    unsigned int seed = 131313;   // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;
    while (*str) {
        hash = hash * seed + (*str++);
    }
    return (hash & 0x7FFFFFFF);
}

static int get_random_str(char* random_str, const int random_len)
{
    int i, random_num, seed_str_len;
    unsigned int seed_num;
    char seed_str[] = "abcdefghijklmnopqrstuvwxyz"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    seed_str_len = strlen(seed_str);
    time_t timep;
    struct tm *p;
    time(&timep);
    p = localtime(&timep); //取得当地具体时间
    seed_num = (unsigned int)(p->tm_min + p->tm_sec);
    srand(seed_num);
    for(i = 0; i < random_len; i++){
        random_num = rand()%seed_str_len;
        random_str[i] = seed_str[random_num];
    }
    return 0;
}

extern void node_map_init()
{
    for(int i=0; i < HASH_DEC_LEN; i++) {
        g_node_map[i].key = NULL;
        g_node_map[i].value = NULL;
        g_node_map[i].next = NULL;
    }
}

extern void map_insert(node_t* n) {
    unsigned int a = BKDRHash(n->name);
    int index = a % HASH_DEC_LEN;
    printf("map insert index: %d\n", index);

    hash_node_t* new_node = (hash_node_t*)malloc(sizeof(hash_node_t));
    if (NULL == new_node) {
        fprintf(stderr, "map insert error");
    }
    new_node->key = n->name;
    new_node->next = NULL;
    new_node->value = n;

    if (g_node_map[index].next == NULL) {
        // 某个节点第一次添加数据
        g_node_map[index].next = new_node;        // g_node_map
    } else {
        // 从头部插入新节点
        new_node->next = g_node_map[index].next;
        g_node_map[index].next = new_node;
    }
}

extern void show_map() {
    hash_node_t* temp;
    for(int i=0; i<HASH_DEC_LEN; i++) {
        printf("index: %d\n", i);
        temp = &g_node_map[i];

        while ( temp != NULL && temp->next != NULL) {
            temp = temp->next;
            printf("node name: %s\n", temp->value->name);
            printf("addr: %s, port: %d\n", temp->value->addr, temp->value->port);
            printf("path1: %s, data: %s\n", temp->value->conf[0].path, temp->value->conf[0].data);
            printf("--->>>\n");
        }
    }
}

extern node_t* map_get_node(char* name) {
    unsigned int index = BKDRHash(name) % HASH_DEC_LEN;
    hash_node_t* temp;
    // 定位桶
    temp = &g_node_map[index]; 
    if (temp == NULL) return NULL;

    while (temp->next != NULL) {
        temp = temp->next; 
        if (strcmp(temp->key, name) == 0) {
            break;
        }
    }
    return temp->value;
}