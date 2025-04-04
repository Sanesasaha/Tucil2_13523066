#include "../header/quadtree.h"
#include "../header/stb_image.h"
#include <cmath>
#include <iostream>
using namespace std;

float QuadTree::channelSSIM(int rgb){
    float C2 = pow(0.03*255, 2);
    return C2/(this->channelVariance(rgb)+C2);
}

float QuadTree::SSIM(){
    return 0.299*this->channelSSIM(0) + 0.587*this->channelSSIM(1) + 0.114*this->channelSSIM(2);
}
