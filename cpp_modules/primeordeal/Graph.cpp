#include "Graph.h"


// void process_data(){
//     Json::Value process_request;
//     ifstream process_request_file("inputoutput/input_data.json", std::ifstream::binary);
//     process_request_file >> process_request;

//     string functname = process_request["functname"].asString();
        
//     if (functname == "contourmesh"){
//         draw_contour(process_request);
//     }
//     if (functname == "traction"){
//         update_displacement_field(process_request);
//     }   
// }

Graph::Graph(const string & reader) {
    Graph g();
    Json::Value process_request;
    ifstream process_request_file("inputoutput/input_data.json", std::ifstream::binary);
    // process_request_file >> process_request;
    // string functname = process_request["functname"].asString();
    cout << reader;
}