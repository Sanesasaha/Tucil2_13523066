#include "../header/quadtree.h"
#include "../header/stb_image.h"
#include "../header/stb_image_write.h"
#include "../header/gif.h"
#include <cmath>
#include <iostream>
using namespace std;

unsigned char** frames;

void QuadTree::generateGIF(const char* img_input_path, const char* img_output_path,  const char* saved_gif_path){
    int w, h, channels;
    frames = new unsigned char*[max_depth];

    for(int i=0;i<max_depth;i++){
        frames[i] = stbi_load(img_input_path, &w, &h, &channels, 4);
        if(frames[i] == nullptr) cout << "AAA";
    }

    this->fillFrames();

    // generate GIF
    GifWriter gif = {};
    if (!GifBegin(&gif, saved_gif_path, original_width, original_height, 100)) {
        cout << "Failed to create GIF\n";
        return;
    }

    for(int i=0;i<max_depth;i++){
        stbi_write_jpg(img_output_path, original_width, original_height, channel, frames[i], 75);
        frames[i] = stbi_load(img_output_path, &w, &h, &channels, 4);
        GifWriteFrame(&gif, frames[i], original_width, original_height, 100);
    }

    // Save
    GifEnd(&gif);
}

void QuadTree::fillFrames(){
    r_avg = this->channelAverage(0);
    g_avg = this->channelAverage(1);
    b_avg = this->channelAverage(2);

    int pixel_index;
    for (int x = x_idx; x < x_idx+width;x++){
        for (int y = y_idx; y < y_idx+height; y++){
            pixel_index = (y * original_width + x) * channel;
            frames[depth-1][pixel_index] = r_avg;
            frames[depth-1][pixel_index+1] = g_avg;
            frames[depth-1][pixel_index+2] = b_avg;
        }
    }
    if(!is_leaf){
        for(int i=0;i<4;i++){
            if(children[i] != nullptr){
                children[i]->fillFrames();
            }
        }
    }
}