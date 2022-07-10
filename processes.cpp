#include "processes.h"
using namespace std;

Curve contours;

// calculate normal vetor at a given point in a curve
Point _normal_vector(Curve c, Point p, float mag){
    auto it = find (c.begin(), c.end(), p);
    int index = it - c.begin();
    if (it != c.end()){
        Ringu<Point> r(c);
        Point p2 = r[index+1], p1 = r[index-1];
        float dx = p2[0] - p1[0], dy = p2[1] - p1[1];
        float dr = sqrt(pow(dx, 2) + pow(dy, 2));
        float costheta = +dy/dr, sintheta = -dx/dr;
        int sign = 1;
        Point normal = { sign * mag * costheta, sign * mag * sintheta};
        return normal;
    }
    else {
        cout<< "\nalert! :point not in curve ";
        return p;
    }
}

void draw_circle(json process_request){
    string values = process_request["values"].asString(); 
    stringstream ss(values);
    string word;
    
}

void draw_contour(map<string, string> data){
    float base_radius = parse_float_number(data.at("radius"));
    string coordinates = data.at("coordinates"); 
    stringstream ss(coordinates);
    string word;
    string coords;
    while(ss >> word){
        cout << word <<"\n";
        Point p = _get_point_coordinates(word);
        int N = 50;   
        for (int F = 3; F <= 10; F ++){
            coords.append("M");
            for (int k = 0 ; k < F * N; k ++ ){
                float theta = k * 2*3.14/(F * N);
                float x = F * base_radius * cos(theta) + p[0];
                float y = F * base_radius * sin(theta) + p[1];
                coords.append(to_string(x));
                coords.append(",");
                coords.append(to_string(y));
                coords.append(" ");        
            }
            coords.append("Z");
        } 

        string output_data = "{\"data\" : \"";
        output_data.append(coords);
        output_data.append("\"}");
        ofstream output_file("inputoutput/output_data.json", std::ifstream::binary);
        output_file << output_data;
        output_file.close();
    }
    // cout << coords;
}

void draw_curve(map<string, string> data){
    Point center = parse_point_2D(data.at("center"));
    string movement = data.at("movement"); 
    stringstream ss;
    string word;
    string coords;
    Curve C;
    int N = 0;
    coords.append("M");
    ss << movement;
    while(ss >> word)
        N+=1;
    ss.clear();
    float delta_theta = 2*3.14/N, theta = 0;
    ss << movement;
    while(ss >> word){
        float r = parse_float_number(word);
        Point dist = {r*cos(theta) + center[0], r*sin(theta) + center[1]};
        coords.append(to_string(dist[0]));
        coords.append(",");
        coords.append(to_string(dist[1]));
        coords.append(" ");
        theta += delta_theta;
        // string output_data = "{\"data\" : \"";
        // output_data.append(coords);
        // output_data.append("\"}");
        // ofstream output_file("inputoutput/output_data.json", std::ifstream::binary);
        // output_file << output_data;
        // output_file.close();
    }
    coords.append("Z");
    cout << coords;
}

// template <class T>


string draw_line_multiple (const string &data){
    int iter = 0;
    string svg_path = "";
    
    istringstream ss(data);

    string word; // for storing each word
    int itertr = 0;
    map<string, string> data_per_line; 
    
    while (ss >> word)
    {        
        if (itertr%3 == 0){
            data_per_line.clear();
            data_per_line.insert(pair<string, string>{"center", word});
        }
        if (itertr%3 == 1){
            data_per_line.insert(pair<string, string>{"angle", word});
        }
        if (itertr%3 == 2){
            data_per_line.insert(pair<string, string>{"length", word});
            svg_path.append(draw_line(data_per_line));
            svg_path.append(" ");
        }
        itertr +=1;
    }

    return svg_path;
}

vector <map<string, string>> * parse_lines (const string &data){
    int iter = 0;
    string svg_path = "";
    
    istringstream ss(data);

    string word; // for storing each word
    int itertr = 0;
    map<string, string> data_per_line;
    vector <map<string, string>>* vector_of_lines; 
    
    while (ss >> word)
    {   
        if (itertr%3 == 0){
            data_per_line.clear();
            data_per_line.insert(pair<string, string>{"center", word});
        }
        if (itertr%3 == 1){
            data_per_line.insert(pair<string, string>{"angle", word});
        }
        if (itertr%3 == 2){
            data_per_line.insert(pair<string, string>{"length", word});
            svg_path.append(draw_line(data_per_line));
            vector_of_lines->push_back(data_per_line);
            svg_path.append(" ");
        }
        itertr +=1;
    }

    return vector_of_lines;
}

vector <map<string, string>> * normalise_line(vector <map<string, string>> *vector_of_lines){

    vector <map<string, string>>* normalizied_vector_of_lines ;

    float sumx = 0, sumy = 0, count = 0, maximx = FLT_MAX, minimx = FLT_MIN;
    float maximy = FLT_MAX, minimy = FLT_MIN; 
    for (auto line_data : *vector_of_lines){
        Point p = parse_point_2D(line_data.at("center"));
        sumx += p[0];
        sumy += p[1];
        count += 1;
    }

    float averagex = 
}


string draw_line(map<string, string> data) {
    Point center  = parse_point_2D(data.at("center"));
    float angle = parse_float_number(data.at("angle"));
    float length = parse_float_number(data.at("length"));
    string svg_path = "";

    stringstream ss;

    float segment = -length/2;
    Point x = {segment*cos(angle), segment*sin(angle)};
    Point new_point =  center + x;  
    ss << new_point[0];
    svg_path.append(ss.str());
    svg_path.append(",");
    ss.str("");
    ss << new_point[1];
    svg_path.append(ss.str());
    svg_path.append(" ");
    ss.str("");

    segment = length/2;
    x = {segment*cos(angle), segment*sin(angle)};
    new_point =  center + x;  
    ss << new_point[0];
    svg_path.append(ss.str());
    svg_path.append(",");
    ss.str("");
    ss << new_point[1];
    svg_path.append(ss.str());
    svg_path.append(" ");
    ss.str("");

    return svg_path;
}

string complete_svg_path(const string &s){
    
    string svg_path = "M ";
    svg_path.append(s);
    svg_path.append("Z");

    return svg_path;
} 

void show_svg_output(const string &s){
    cout<< s;
}

void update_displacement_field(json process_request){
    int no_of_contours = 40;
    string values = process_request["values"]["displacement"].asString(); 
    stringstream ss;
    ss << values;
    Curve boundary_displacement_field;
    string word;
    while(ss >> word){
        Point p = _get_point_coordinates(word);
        boundary_displacement_field.push_back(p);
    }

    ss.clear();
    values.clear();

    values = process_request["values"]["boundary"].asString(); 
    ss << values;
    Curve boundary;
    while(ss >> word){
        Point p = _get_point_coordinates(word);
        boundary.push_back(p);
    }

    using namespace Eigen;
    Curve new_boundary = boundary, current_boundary; 
    Point new_p;
    string coords;
    
    for (int i_contour = 1; i_contour < no_of_contours; i_contour++){
        coords.append("M ");
        Copy_curve(new_boundary, current_boundary);
        new_boundary.clear();
        for (auto p : current_boundary){
            Point normal = _normal_vector(current_boundary, p, 10.0);
            new_p = p + normal;
            new_boundary.push_back(new_p);
            coords.append(to_string(new_p[0]));
            coords.append(",");
            coords.append(to_string(new_p[1]));
            coords.append(" ");        
        }
        coords.append("Z ");
    }

    string output_data = "{\"data\" : \"";
    output_data.append(coords);
    output_data.append("\"}");
    ofstream output_file("inputoutput/output_data.json", std::ifstream::binary);
    output_file << output_data;
    output_file.close();   
}


void create_visulaisation(json process_request){

}