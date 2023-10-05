#ifndef _DMF_NODE_MAP_H_
#define _DMF_NODE_MAP_H_

// 每个节点都会维护一个保存所有节点的 hashmap
// key => node->name , value => node

#include "dmf_node.h"

#define HASH_DEC_LEN    13


typedef struct _hash_node_t {
    
    char                   *       key;
    node_t                 *       value;
    struct _hash_node_t    *       next; // 当下标相同时，指向下一个节点

} hash_node_t ;

extern hash_node_t g_node_map[ HASH_DEC_LEN ];

extern void node_map_init();

extern void map_insert(node_t* n);

extern node_t* map_get_node(char* name);

extern void show_map() ;


#endif  //_DMF_NODE_MAP_H_