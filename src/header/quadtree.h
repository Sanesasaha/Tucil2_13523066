#ifndef __QUADTREE__HPP__
#define __QUADTREE__HPP__

class QuadTree{
private:
    static const char *img_path;
    static int error_measurement_method;
    static float threshold;
    static int min_size;
    static int node_count;
    // static float compression_target; // [BONUS]

    int depth;
    int x_idx;
    int y_idx;
    int width;
    int height;
    int block_size;
    float error_result;
    bool is_leaf;
    QuadTree* children;
public:
    QuadTree();
    QuadTree(int depth, int x_idx, int y_idx, int width, int height);
    
    void compressImage(const char* saved_img_path);
    // void generateGIF(const char* saved_img_path); // [BONUS]

    float variance();
    float MAD();
    float MPD();
    float entropy();
    // float SSIM(); // [BONUS]
};

#endif