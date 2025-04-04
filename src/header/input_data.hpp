#ifndef __INPUTDATA__HPP__
#define __INPUTDATA__HPP__

#include <string>
using namespace std;

class InputData{
public:
    string img_input_string;
    const char *img_input_path; 
    int error_measurement_method;
    float threshold;
    int min_block_size;
    float compression_pct;
    string img_output_string;
    const char *img_output_path;
    string gif_string;
    const char *gif_path;

    bool validate();
};

#endif