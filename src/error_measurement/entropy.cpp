#include "../header/quadtree.h"
#include "../header/stb_image.h"
#include <cmath>
#include <iostream>
using namespace std;


// Menghitung entropy suatu channel R, G, B, dengan nilai int rgb berturut turut 0, 1, 2
float QuadTree::channelEntropy(int rgb){
    float result = 0;
    
    int pixel_index;
    for(int x=x_idx;x<x_idx+width;x++){
        for(int y=y_idx;y<y_idx+height;y++){
            pixel_index = (y * original_width + x) * channel;
            // TODO
        }
    }

    return result;
}

float QuadTree::entropy(){
    float result =  this->channelEntropy(0) + this->channelEntropy(1) + this->channelEntropy(2);
    result/=3;
    return result;
}