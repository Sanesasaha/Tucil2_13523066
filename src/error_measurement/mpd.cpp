#include "../header/quadtree.h"
#include "../header/stb_image.h"
#include <cmath>
#include <iostream>
using namespace std;


// Menghitung MPD suatu channel R, G, B, dengan nilai int rgb berturut turut 0, 1, 2
float QuadTree::channelMPD(int rgb){
    float channel_max = -1;
    float channel_min = 300;
    
    int pixel_index;
    for(int x=x_idx;x<x_idx+width;x++){
        for(int y=y_idx;y<y_idx+height;y++){
            pixel_index = (y * original_width + x) * channel;
            channel_max = fmax(img[pixel_index + rgb], channel_max);
            channel_min = fmin(img[pixel_index + rgb], channel_min);
        }
    }

    return (channel_max - channel_min);
}

float QuadTree::MPD(){
    float result =  this->channelMAD(0) + this->channelMAD(1) + this->channelMAD(2);
    result/=3;
    return result;
}