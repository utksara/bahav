#include "cpp_modules/dist/json/json.h"
#include "cpp_modules/utils.h"
#include <Eigen/Dense>
#ifndef INCLUDE_PRIMEORDEAL_GEOMETRY
    #include "cpp_modules/primeordeal/geometry.h"
#endif


using namespace std;

typedef Json::Value json;

Point read_int(string word);
void draw_contour(map<string, string> data);
void update_displacement_field(json process_request);
void draw_line(map<string, string> data);
void draw_curve(map<string, string> data);