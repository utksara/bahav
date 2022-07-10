
#include<iostream>
#include<fstream>
#include<sstream>
#include "processes.h"
#ifndef LIB_JSONCPP_JSON_TOOL_H_INCLUDED
    #include "cpp_modules/dist/json/json.h"
#endif
enum distanc_unit {cm, mm, nm, um};
enum force_unit {mN, N, uN};

using namespace std;

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

/**
 * Types of shapes
 *  Point
 *  Closed Curve 
 *  Line
 * 
 * Types of quantities
 *  scalar
 *  vector
 *  none
 * 
 * Types of valid combinations of shapes and quantities
 *  none is valid with every shape
 *  (Point, scalar)
 *  (Point, vector)
 *  (Line, scalar)
 *  (Curve, scalar)
 *  (Curve, vector)
 *  
 */

int main(int argc, char** argv){
    if (argc <=1){
        // process_data();
    }
    else{
        map<string, string> data; 
        string data_sting;
        string func = argv[1];
        string second_arg = argv[2];
        bool contagious_data = second_arg.compare("contagious");
        if (contagious_data != 0){
            for (int i = 2; i+1 < argc; i+=2){
                data.insert(pair<string, string>(argv[i], argv[i+1]));
                // cout <<"\n here"<< argv[i] << ", " <<  argv[i+1] << endl;
            }
        }
        else{
            data_sting = argv[3];
        }
        if (func.compare("line") == 0){
            show_svg_output( draw_line(data));
        }
        if (func.compare("multiline") == 0){
            show_svg_output( draw_line_multiple(data_sting));
        }
        if(func.compare("contour") == 0){
            draw_contour(data);
        }
        if(func.compare("curve") == 0){
            draw_curve(data);
        }
        if(func.compare("graph") == 0){
            Graph g(argv[2]);
        }
        // else if (func == "curve"){
        //     cout << "\nhellow ";
        //     draw_line(data);
        // }
    }
}