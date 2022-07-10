#include "cpp_modules/dist/json/json.h"
#include "cpp_modules/primeordeal/Graph.h"
#ifndef INCLUDE_SYSTEM
    #include "cpp_modules/primeordeal/system.h"
#endif
#ifndef INCLUDE_UTILS
    #include "cpp_modules/utils.h"
#endif
#include <Eigen/Dense>
#ifndef INCLUDE_PRIMEORDEAL_GEOMETRY
    #include "cpp_modules/primeordeal/geometry.h"
#endif


using namespace std;

typedef Json::Value json;

Point read_int(string word);
void draw_contour(map<string, string> data);
void update_displacement_field(json process_request);
string draw_line(map<string, string> data);
string draw_line_multiple(const string &s);
string complete_svg_path(const string &s);
void show_svg_output(const string &s);
void draw_curve(map<string, string> data);