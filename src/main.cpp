#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
using namespace std;
using namespace chrono;

#define STB_IMAGE_IMPLEMENTATION
#include "header/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "header/stb_image_write.h"

#include "header/quadtree.h"
#include "header/input_data.hpp"

int main(){
    int w, h, channels;
    float input_file_size;
    float output_file_size;

    unsigned char *img;
    unsigned char *compressed_img;
    bool run = true;
    bool is_valid = true;
    string cont;
    
    while(run){
        InputData data;
        // TODO: VALIDATION
        cout << "Absolute Path to Image        : " << endl;
        getline(cin, data.img_input_string);
        data.img_input_path = data.img_input_string.c_str();

        cout << "Error Measurement Method      : ";
        cin >> data.error_measurement_method;
        while(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Harap masukkan angka dalam rentang 1-5" << endl;

            cout << "Error Measurement Method      : ";
            cin >> data.error_measurement_method;
        }

        cout << "Threshold                     : ";
        cin >> data.threshold;
        while(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Harap masukkan angka dalam rentang yang valid" << endl;

            cout << "Threshold                     : ";
            cin >> data.threshold;
        }

        cout << "Minimum Block Size            : ";
        cin >> data.min_block_size;
        while(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Harap masukkan angka dalam rentang yang valid" << endl;

            cout << "Minimum Block Size            : ";
            cin >> data.min_block_size;
        }

        cout << "Compression Percentage Target : ";
        cin >> data.compression_pct;
        while(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Harap masukkan angka dalam rentang yang valid" << endl;

            cout << "Compression Percentage Target : ";
            cin >> data.compression_pct;
        }

        cout << "Absolute Path to Result       : " << endl;
        cin.ignore();
        getline(cin, data.img_output_string);
        data.img_output_path = data.img_output_string.c_str();

        cout << "Absolute Path to GIF          : " << endl;
        getline(cin, data.gif_string);
        data.gif_path = data.gif_string.c_str();
        
        is_valid = data.validate();
        if(is_valid){
            cout << "Generating image ..." << endl;
            // Compression
            img = stbi_load(data.img_input_path, &w, &h, &channels, 0);
            compressed_img = stbi_load(data.img_input_path, &w, &h, &channels, 0);
    
            QuadTree qt = QuadTree(1,0,0,w,h);
            qt.setStatic(img, compressed_img, data.error_measurement_method, data.threshold, data.min_block_size, channels);
            
            auto start = high_resolution_clock::now();
            if(data.compression_pct == 0){
                qt.compressImage();
            } else{
                qt.compressImageByFileSize(data.compression_pct, 0, 255, data.img_input_path, data.img_output_path);
            }
            auto end = high_resolution_clock::now();
            auto exec_time = duration_cast<milliseconds>(end-start);
    
            cout << "Saving image ..." << endl;
            qt.saveCompressedImage(data.img_output_path);
            cout << "Saving GIF ..." << endl;
            qt.generateGIF(data.img_output_path, data.gif_path);
            
            ifstream file(data.img_input_path, ios::binary | ios::ate);
            streamsize size = file.tellg();
            input_file_size = static_cast<float>(size / 1024);
            
            ifstream file2(data.img_output_path, ios::binary | ios::ate);
            size = file2.tellg();
            output_file_size = static_cast<float>(size / 1024);
    
            cout << endl;
            cout << "Execution Time (ms)   : " << exec_time.count() << endl;
            cout << "Input File Size       : " << input_file_size << endl;
            cout << "Output File Size      : " << output_file_size << endl;
            cout << "Compression Percentage: " << qt.final_compression_pct*100 << "%" << endl;
            cout << "Tree Depth            : " << qt.getMaxDepth() << endl;
            cout << "Node Count            : " << qt.getNodeCount() << endl;
            
    
            cout << endl << "Continue?" << endl;
            cout << "(Input Y to continue, anything else to quit)" << endl;
            getline(cin, cont);
            if(cont != "Y"){
                run = false;
            }
        }
    }

    return 0;
}