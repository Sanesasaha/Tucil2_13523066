#include "../header/quadtree.h"
#include "../header/stb_image.h"
#include "../header/stb_image_write.h"
#include "../header/gif.h"
#include "../header/gif_generator.h"
#include <regex>
#include <cmath>
#include <iostream>
using namespace std;

unsigned char** frames;

void QuadTree::generateGIF(const char* img_output_path,  const char* saved_gif_path){
    int w, h, channels;
    frames = new unsigned char*[max_depth];

    // Generate setiap frame
    for(int i=0;i<max_depth;i++){
        frames[i] = stbi_load(img_output_path, &w, &h, &channels, 4);
        if(frames[i] == nullptr) cout << "AAA";
    }
    
    // Isi setiap frame
    this->fillFrames();

    // Generate GIF
    GifWriter gif = {};
    if (!GifBegin(&gif, saved_gif_path, original_width, original_height, 100)) {
        cout << "Failed to create GIF" << endl;;
        return;
    }

    regex path_png(".*\\.png$");
    for(int i=0;i<max_depth;i++){
        if(regex_match(img_output_path, path_png)){
            stbi_write_png(img_output_path, width, height, channel, frames[i], width * channel);
        } else{
            stbi_write_jpg(img_output_path, width, height, channel, frames[i], 75);
        }
        frames[i] = stbi_load(img_output_path, &w, &h, &channels, 4);
        GifWriteFrame(&gif, frames[i], original_width, original_height, 100);
    }

    // Save
    GifEnd(&gif);
}

void QuadTree::fillFrames(){
    // Untuk node pada depth tertentu, isi blok yang ditinjau oleh node pada frame ke-(depth-1) hingga depth terakhir
    // dengan rerata dari pixel pada blok tersebut (frame dihitung dari 0)
    r_avg = this->channelAverage(0);
    g_avg = this->channelAverage(1);
    b_avg = this->channelAverage(2);

    int pixel_index;
    for (int x = x_idx; x < x_idx+width;x++){
        for (int y = y_idx; y < y_idx+height; y++){
            pixel_index = (y * original_width + x) * channel;
            for(int d=depth-1;d<max_depth;d++){
                frames[d][pixel_index] = r_avg;
                frames[d][pixel_index+1] = g_avg;
                frames[d][pixel_index+2] = b_avg;
            }
        }
    }
    // telusuri seluruh child node
    if(!is_leaf){
        for(int i=0;i<4;i++){
            if(children[i] != nullptr){
                children[i]->fillFrames();
            }
        }
    }
}

bool saveGIFTemplate(const char* input_filename, const char* filename){
    int w, h, channels;
    unsigned char* img = stbi_load(input_filename, &w, &h, &channels, 0);
    
    GifWriter gif = {};
    if (!GifBegin(&gif, filename, w, h, 100)) {
        cout << "Failed to create GIF" << endl;
        return false;
    }
    return true;
}