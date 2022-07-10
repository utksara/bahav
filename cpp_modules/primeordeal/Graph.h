#include "system.h"
#include "../../cpp_modules/dist/json/json.h"

const int MAX_SIZE_OF_GRAPH = 65000; 

struct Graph{
    array<EDGE, MAX_SIZE_OF_GRAPH> edges;
    // map<ID, SYSTEM> sys_by_id;
    map<EDGE, SYSTEM> edge_by_id;
    Graph(const string &reader);
    Graph();
};

// string traverseDFS (Graph g, ID id){
//     auto it = g.sys_by_id.find(id);
//     while(it != g.sys_by_id.end()){
//         it = it->next;
//     }
// }