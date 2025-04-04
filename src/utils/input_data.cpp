#include <iostream>
#include <string>
#include <regex>
#include <fstream>
using namespace std;

#include "../header/stb_image.h"
#include "../header/stb_image_write.h"
#include "../header/gif_generator.h"
#include "../header/input_data.hpp"

bool validateImageFile(const char* filename){
    regex windows_absolute_path("^[A-Za-z]:[\\/].*\\.(jpg|jpeg|png)$");
    regex linux_absolute_path("^/.*\\.(jpg|jpeg|png)$");

    if(!(regex_match(filename, windows_absolute_path) || regex_match(filename, linux_absolute_path))){
        cout << "Format file tidak valid!" << endl;
    }
    return true;
}

bool validateGIFFile(const char* filename){
    regex windows_absolute_path("^[A-Za-z]:[\\/].*\\.gif$");
    regex linux_absolute_path("^/.*\\.gif$");

    if(!(regex_match(filename, windows_absolute_path) || regex_match(filename, linux_absolute_path))){
        cout << "Format file tidak valid!" << endl;
    }
    return true;
}

bool inputPathExist(const char* filename){
    if(!validateImageFile(filename)) return false;
    int w, h, channels;
    unsigned char* img = stbi_load(filename, &w, &h, &channels, 0);
    if(img==nullptr){
        cout << "File tidak ditemukan!" << endl;
        return false;
    }
    return true;
}

bool validateErrorMethod(int emm){
    if(emm<1 || emm>5){
        cout << "Harap masukkan angka dalam rentang 1-5" << endl;
        return false;
    } 
    return true;
}

bool validateThreshold(int emm, float thresh){
    // TODO: CEK
    if(!validateErrorMethod) return false;
    if(emm==1){
        if(thresh>=0 && thresh<=16256.25){
            return true;
        }
    }
    else if(emm==2){
        if(thresh>=0 && thresh<=127.5){
            return true;
        }
    }
    else if(emm==3){
        if(thresh>=0 && thresh<=255){
            return true;
        }
    }
    else if(emm==4){
        if(thresh>=0 && thresh<=8){
            return true;
        }
    }
    else if(emm==5){
        if(thresh>=0 && thresh<=1){
            return true;
        }
    }
    else{
        cout << "Nilai threshold tidak valid!" << endl;
        return false;
    }
}

bool validateMinBlockSize(const char* filename, int mbs){
    if(!inputPathExist(filename)) return false;
    int w, h, channels;
    unsigned char* img = stbi_load(filename, &w, &h, &channels, 0);

    if(mbs>=1 && mbs <= w*h){
        return true;
    } else{
        cout << "Nilai minimum block size tidak valid!" << endl;
        return false;
    }
}

bool validateCompressionPct(float pct){
    if(pct>=0 && pct<=1){
        return true;
    } else{
        cout << "Nilai target persentase kompresi tidak valid!" << endl;
        return false;
    }
}

bool validateOutputPath(const char* input_filename, const char* filename){
    if(!inputPathExist(input_filename)) return false;
    if(!validateImageFile(filename)) return false;

    int w, h, channels;
    unsigned char* img = stbi_load(input_filename, &w, &h, &channels, 0);
    
    regex path_png(".*\\.png$");
    if(regex_match(filename, path_png)){
        stbi_write_png(filename, w, h, channels, img, w*channels);
    } else{
        stbi_write_jpg(filename, w, h, channels, img, 75);
    }

    unsigned char* img2 = stbi_load(filename, &w, &h, &channels, 0);
    if(img2==nullptr){
        cout << "Path output tidak valid!" << endl;
        return false;
    }
    return true;
}

bool validateGIFPath(const char* input_filename, const char* filename){
    if(!inputPathExist(input_filename)) return false;
    if(!validateGIFFile(filename)) return false;

    return saveGIFTemplate(input_filename, filename);
}

bool InputData::validate(){
    bool isValid = true;
    cout << endl;
    isValid = isValid && validateImageFile(img_input_path);
    isValid = isValid && inputPathExist(img_input_path);
    isValid = isValid && validateErrorMethod(error_measurement_method);
    isValid = isValid && validateThreshold(error_measurement_method, threshold);
    isValid = isValid && validateMinBlockSize(img_input_path, min_block_size);
    isValid = isValid && validateCompressionPct(compression_pct);
    isValid = isValid && validateOutputPath(img_input_path, img_output_path);
    isValid = isValid && validateGIFPath(img_input_path, img_output_path);
    cout << endl;
    return isValid;
}