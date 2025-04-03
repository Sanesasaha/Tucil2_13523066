#include <iostream>
#include <stdlib.h>
#include <string>
#include <chrono>
using namespace std;
using namespace chrono;

#define STB_IMAGE_IMPLEMENTATION
#include "header/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "header/stb_image_write.h"

#include "header/quadtree.h"

int main(){
    int w, h, channels;
    const char *img_input_path; 
    string img_input_string;
    int error_measurement_method;
    float threshold;
    int min_block_size;
    const char *img_output_path;
    string img_output_string;

    float input_file_size;
    float output_file_size;
    int depth;
    int node_count;

    unsigned char *img;
    unsigned char *compressed_img;
    bool run = true;
    string cont;
    while(run){
        // TODO: VALIDATION
        cout << "Absolute Path to Image  : " << endl;
        getline(cin, img_input_string);
        img_input_path = img_input_string.c_str();

        cout << "Error Measurement Method: ";
        cin >> error_measurement_method;
        
        cout << "Threshold               : ";
        cin >> threshold;

        cout << "Minimum Block Size      : ";
        cin >> min_block_size;

        cout << "Absolute Path to Result : " << endl;
        cin.ignore();
        getline(cin, img_output_string);
        img_output_path = img_output_string.c_str();

        // Compression
        img = stbi_load(img_input_path, &w, &h, &channels, 0);
        compressed_img = stbi_load(img_input_path, &w, &h, &channels, 0);

        QuadTree qt = QuadTree(1,0,0,w,h);
        qt.setStatic(img, compressed_img, error_measurement_method, threshold, min_block_size, channels);
        
        auto start = high_resolution_clock::now();
        qt.compressImage();
        auto end = high_resolution_clock::now();
        auto exec_time = duration_cast<milliseconds>(end-start);

        qt.saveCompressedImageJPG(img_output_path);
        
        cout << endl;
        cout << "Execution Time (ms)   : " << exec_time.count() << endl;
        cout << "Input File Size       : " << input_file_size << endl;
        cout << "Output File Size      : " << output_file_size << endl;
        cout << "Compression Percentage: " << (output_file_size-input_file_size)/input_file_size << "%" << endl;
        cout << "Tree Depth            : " << qt.getMaxDepth() << endl;
        cout << "Node Count            : " << qt.getNodeCount() << endl;
        
        qt.generateGIF(img_input_path, img_output_path, "bin/img_output/bocchi.gif");

        cout << endl << "Continue?" << endl;
        cout << "(Input Y to continue, anything else to quit)" << endl;
        getline(cin, cont);
        if(cont != "Y"){
            run = false;
        }
    }

    return 0;
}