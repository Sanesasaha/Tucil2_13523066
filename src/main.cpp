#include <iostream>
#include <stdlib.h>
using namespace std;

#define STB_IMAGE_IMPLEMENTATION
#include "header/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "header/stb_image_write.h"

#include "header/quadtree.h"

int main(){
    int w, h, channels;
    const char *img_path = "bin/img_input/shioriko.jpeg";
    unsigned char *img = stbi_load(img_path, &w, &h, &channels, 0);
    unsigned char *compressed_img = stbi_load(img_path, &w, &h, &channels, 0);
    if(img==NULL){
        cout << "ERROR" << endl;
    }
    // cout << w << endl;
    // cout << h << endl;
    // cout << channels << endl;

    QuadTree qt = QuadTree(1, 0, 0, w, h);
    qt.setStatic(img, compressed_img, 1, 50, 256, channels);
    qt.compressImage();
    qt.saveCompressedImage("bin/img_output/shioriko-compressed.jpeg");

    stbi_image_free(img);
    stbi_image_free(compressed_img);
    return 0;
}