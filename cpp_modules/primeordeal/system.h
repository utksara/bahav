#include<iostream>
#include<stdio.h>
// #include"geometry.h"
#include "../utils.h"

#define INCLUDE_SYSTEM 1;

using namespace std;

typedef string SCHEMA;
typedef string ID;
typedef array<ID, 2> EDGE;
typedef map<string, string> EDGE_DATA;
typedef map<string, string> PARAMS;

template <typename T> struct TYPE {
    typedef array<pair<string, T>, 2> _SINGLE_VALUES;
    typedef array<pair<string, array<T, 2>>, 2> _ARRAY;
};

struct SYSTEM {
    ID id;
    map<string, string> processes;
    vector<ID> require;
    vector<string> visualize;
    vector<ID> TO;
    EDGE_DATA ed;
    SYSTEM(SCHEMA param);
};

EDGE_DATA merge_edge_data (EDGE_DATA new_ed, EDGE_DATA old_ed);

EDGE_DATA execute_function(string f_name, PARAMS args);

EDGE_DATA process_system(SYSTEM s, EDGE_DATA args);