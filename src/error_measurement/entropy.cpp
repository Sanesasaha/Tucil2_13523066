#include "../header/quadtree.h"
#include "../header/stb_image.h"
#include <cmath>
#include <iostream>
using namespace std;


// Menghitung entropy suatu channel R, G, B, dengan nilai int rgb berturut turut 0, 1, 2
float QuadTree::channelEntropy(int rgb){
    int count[256] = {0};
    float result = 0;
    
    int pixel_index;
    // Banyak kemunculan nilai RGB tertentu
    for(int x=x_idx;x<x_idx+width;x++){
        for(int y=y_idx;y<y_idx+height;y++){
            pixel_index = (y * original_width + x) * channel;
            count[img[pixel_index + rgb]]++;
        }
    }

    // Entropi
    float probability;
    for(int i=0;i<256;i++){
        probability = count[i]/block_size;
        result += (probability*log2(probability));
    }

    return -1*result;
}

float QuadTree::entropy(){
    float result =  this->channelEntropy(0) + this->channelEntropy(1) + this->channelEntropy(2);
    result/=3;
    return result;
}