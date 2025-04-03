#include "../header/quadtree.h"
#include "../header/stb_image.h"
#include <cmath>
#include <iostream>
using namespace std;


// Menghitung MAD suatu channel R, G, B, dengan nilai int rgb berturut turut 0, 1, 2
float QuadTree::channelMAD(int rgb){
    float result = 0;
    float avg = this->channelAverage(rgb);
    
    int pixel_index;
    for(int x=x_idx;x<x_idx+width;x++){
        for(int y=y_idx;y<y_idx+height;y++){
            pixel_index = (y * original_width + x) * channel;
            result += abs(img[pixel_index + rgb] - avg);
        }
    }
    result = result/block_size;
    return result;
}

float QuadTree::MAD(){
    float result =  this->channelMAD(0) + this->channelMAD(1) + this->channelMAD(2);
    result/=3;
    return result;
}