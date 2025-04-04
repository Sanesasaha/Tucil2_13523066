#include "../header/quadtree.h"
#include "../header/stb_image_write.h"
#include <iostream>
using namespace std;

unsigned char* QuadTree::img =nullptr;
int QuadTree::original_width = -1;
int QuadTree::original_height = -1;
unsigned char* QuadTree::compressed_img = nullptr;
int QuadTree::error_measurement_method = -1;
float QuadTree::threshold = -1;
int QuadTree::min_block_size = -1;
int QuadTree::node_count = -1;
int QuadTree::max_depth = -1;
int QuadTree::channel = -1;

QuadTree::QuadTree(int depth, int x_idx, int y_idx, int width, int height){
    this->depth = depth;
    this->x_idx = x_idx;
    this->y_idx = y_idx;
    this->width = width;
    this->height = height;
    this->block_size = width*height;
    this->error_result = -1;
    this->is_leaf = false;

    for(int i=0;i<4;i++){
        this->children[i] = nullptr;
    }

    node_count++;

    if(this->depth > max_depth){
        max_depth = this->depth;
    }

    this->r_avg = -1;
    this->g_avg = -1;
    this->b_avg = -1;
}

void QuadTree::setStatic(unsigned char* img, unsigned char* compressed_img, int error_measurement_method, float threshold, int min_size, int channel){
    this->img = img;
    this->original_width = width;
    this->original_height = height;
    this->compressed_img = compressed_img;
    this->error_measurement_method = error_measurement_method;
    this->threshold = threshold;
    this->min_block_size = min_size;
    this->node_count = 1;
    this->max_depth = 1;
    this->channel = channel;
}

void QuadTree::compressImage(){
    is_leaf = false;
    if(block_size<=min_block_size){
        is_leaf = true;
    } else if(error_measurement_method==1){ // variance
        error_result = this->variance();
        if(error_result<=threshold){
            is_leaf = true;
        }
    } else if(error_measurement_method==2){ // MAD
        error_result = this->MAD();
        if(error_result<=threshold){
            is_leaf = true;
        }
    } else if(error_measurement_method==3){ // MPD
        error_result = this->MPD();
        if(error_result<=threshold){
            is_leaf = true;
        }
    } else if(error_measurement_method==4){ // entropy
        error_result = this->entropy();
        if(error_result<=threshold){
            is_leaf = true;
        }
    } else if(error_measurement_method==5){ // entropy
        error_result = this->SSIM();
        if(error_result>=threshold){
            is_leaf = true;
        }
    }

    if(!is_leaf){ // DIVIDE
        int width_increment = 0;
        int height_increment = 0;
        if(width%2==1) width_increment = 1;
        if(height%2==1) height_increment = 1;
        
        int half_width = width/2;
        int half_height = height/2;
        // top left
        children[0] = new QuadTree(depth+1, x_idx, y_idx, half_width, half_height);
        // top right
        if(half_width!=0) children[1] = new QuadTree(depth+1, x_idx + half_width, y_idx, half_width + width_increment, half_height);
        // bottom left
        if(half_height!=0) children[2] = new QuadTree(depth+1, x_idx, y_idx + half_height, half_width, half_height + height_increment);
        // bottom right
        children[3] = new QuadTree(depth+1, x_idx + half_width, y_idx + half_height, half_width + width_increment, half_height + height_increment);

        for(int i=0;i<4;i++){
            if(children[i] != nullptr) children[i]->compressImage();
        }
    } else{ // CONQUER
        r_avg = this->channelAverage(0);
        g_avg = this->channelAverage(1);
        b_avg = this->channelAverage(2);
        
        
        int pixel_index;
        for (int x = x_idx; x < x_idx+width;x++){
            for (int y = y_idx; y < y_idx+height; y++){
                pixel_index = (y * original_width + x) * channel;
                compressed_img[pixel_index] = r_avg;
                compressed_img[pixel_index+1] = g_avg;
                compressed_img[pixel_index+2] = b_avg;
            }
        }
    }
}

void QuadTree::saveCompressedImageJPG(const char* path){
    stbi_write_jpg(path, width, height, channel, this->compressed_img, 75);
}

void QuadTree::saveCompressedImagePNG(const char* path){
    stbi_write_png(path, width, height, channel, this->compressed_img, width * channel);
}

int QuadTree::getMaxDepth(){
    return this->max_depth;
}
int QuadTree::getNodeCount(){
    return this->node_count;
}