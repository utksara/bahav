#include <map>
#include <vector>
#include <utility>
#include <stdexcept>
#include <bits/stl_algobase.h>
#include <bits/range_access.h>
#include <array>
#include<iostream>

#include "system.h"

#define INCLUDE_IOSTREAM 1

EDGE_DATA merge_edge_data (EDGE_DATA new_ed, EDGE_DATA old_ed){
    for (auto new_itr = new_ed.begin(); new_itr != new_ed.end(); new_itr++){
        auto old_itr = old_ed.find(new_itr->first);
        if (old_itr != old_ed.end()){
            old_itr->second = new_itr->second;
        }else{
            old_ed.insert({new_itr->first, new_itr->second});
        }
    }
    return old_ed;
}

EDGE_DATA execute_function(string f_name, PARAMS args){
    EDGE_DATA reduced_data;
    float reduced_num = 0;
    for (auto itr = args.begin(); itr != args.end(); itr++){
        float new_num = parse_float_number(itr->second);
        reduced_num += new_num;
    }
    reduced_data.insert({f_name, std::to_string(reduced_num)});
    return reduced_data;
}


EDGE_DATA process_system(SYSTEM s, EDGE_DATA args){
    EDGE_DATA updated_ed;
    for (auto f_itr = s.processes.begin(); f_itr != s.processes.end(); f_itr++){
        EDGE_DATA new_ed = execute_function(f_itr->first, args);
        new_ed = merge_edge_data (new_ed, updated_ed);
    }
    return updated_ed;
}

// void CREATE_NEW_SYSTEM();
// void CREATE_COPIES_OF_SYSTEM(SYSTEM S, int N);
// void CONNECT_SYSTEMS(SYSTEM PARENT, SYSTEM CHILDREN);
// void PARALLELISE_SYSTEMS(SYSTEM S1, SYSTEM S2);