#include "../header/quadtree.h"
#include "../header/stb_image.h"
#include <cmath>
#include <iostream>
using namespace std;

float QuadTree::channelAverage(int rgb){
    float avg = 0;
    int pixel_index;

    for(int x=x_idx;x<x_idx+width;x++){
        for(int y=y_idx;y<y_idx+height;y++){
            pixel_index = (y * original_width + x) * channel;
            avg += img[pixel_index + rgb];   
        }
    }
    avg /= block_size;
    return avg;
}

// Menghitung variansi suatu channel R, G, B, dengan nilai int rgb berturut turut 0, 1, 2
float QuadTree::channelVariance(int rgb){
    float result = 0;
    float avg = 0;
    float sum_of_squared = 0;
    int pixel_index;

    for(int x=x_idx;x<x_idx+width;x++){
        for(int y=y_idx;y<y_idx+height;y++){
            pixel_index = (y * original_width + x) * channel;
            avg += img[pixel_index + rgb];
            sum_of_squared += pow(img[pixel_index + rgb], 2);
        }
    }
    result = sum_of_squared/block_size - pow(avg/block_size, 2);
    return result;
}

float QuadTree::variance(){
    float result =  pow(this->channelVariance(0), 2) + pow(this->channelVariance(1), 2) + pow(this->channelVariance(2), 2);
    result/=3;
    return result;
}