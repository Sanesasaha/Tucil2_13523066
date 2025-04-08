#include "../header/quadtree.h"
#include "../header/stb_image.h"
#include <cmath>
#include <iostream>
#include <fstream>
using namespace std;

void QuadTree::setThreshold(float thresh){
    this->threshold = thresh;
}

void QuadTree::setMinBlockSize(float mbs){
    this->min_block_size = mbs;
}

void QuadTree::resetRelevantData(int depth, int node_count){
    this->depth = depth;
    this->node_count = node_count;
}

void QuadTree::compressImageByFileSize(float compression_pct, int emm, const char* img_input_path, const char* img_output_path){
    // Hitung ukuran file input
    ifstream file(img_input_path, ios::binary | ios::ate);
    streamsize size = file.tellg();
    float input_file_size = static_cast<float>(size / 1024);

    float current_pct;
    float output_file_size;

    float current_min = 0;
    float current_max;

    if(emm==1){
        current_max = 16256.25;
    } else if(emm==2){
        current_max = 127.5;
    } else if(emm==3){
        current_max = 255;
    } else if(emm==4){
        current_max = 8;
    } else if(emm==5){
        current_max = 1;
    }

    // Asumsikan min block size bernilai 1
    this->setMinBlockSize(1);

    // Mulai binary search
    for(int i=0;i<20;i++){
        // Ambil bagian tengah dari range nilai
        this->setThreshold((current_min+current_max)/2);
        // Kompresi
        this->resetRelevantData(1,1);
        this->compressImage();
        this->saveCompressedImage(img_output_path);

        // Hitung ukuran file output, bandingkan
        ifstream file2(img_output_path, ios::binary | ios::ate);
        size = file2.tellg();
        output_file_size = static_cast<float>(size / 1024);

        current_pct = (input_file_size-output_file_size)/input_file_size;
        final_compression_pct = current_pct;
        
        // Evaluasi range binary search
        if(abs(current_pct - compression_pct) < 0.01){
            return;
        } else if(current_pct > compression_pct){
            if(error_measurement_method==5){
                current_min = this->threshold;
            } else{
                current_max = this->threshold;
            }
        } else{
            if(error_measurement_method==5){
                current_max = this->threshold;
            } else{
                current_min = this->threshold;
            }
        }
    }
}