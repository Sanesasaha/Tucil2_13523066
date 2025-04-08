#ifndef __QUADTREE__HPP__
#define __QUADTREE__HPP__

class QuadTree{
private:
    static unsigned char *img;
    static int original_width;
    static int original_height;
    static unsigned char *compressed_img;
    static int error_measurement_method;
    static float threshold;
    static int min_block_size;
    static int node_count;
    static int max_depth;
    static float compression_target;

    int depth;
    int x_idx;
    int y_idx;
    int width;
    int height;
    static int channel;
    int block_size;
    float error_result;
    bool is_leaf;
    QuadTree* children[4];

    float r_avg;
    float g_avg;
    float b_avg;
public:
    // Konstruktor
    QuadTree(int depth, int x_idx, int y_idx, int width, int height);
    
    // Kompresi gambar
    void compressImage();
    void saveCompressedImage(const char* path);
    void saveCompressedImageJPG(const char* path);
    void saveCompressedImagePNG(const char* path);
    
    // Bonus GIF
    void generateGIF(const char* img_output_path,  const char* saved_gif_path);
    void fillFrames();

    // Error measurement methods
    float variance();
    float channelVariance(int rgb);
    float channelAverage(int rgb);

    float MAD();
    float channelMAD(int rgb);

    float MPD();
    float channelMPD(int rgb);

    float entropy();
    float channelEntropy(int rgb);

    float SSIM();
    float channelSSIM(int rgb);

    // Dynamic compression
    void compressImageByFileSize(float compression_pct, int emm, const char* img_input_path, const char* img_output_path);
    void setThreshold(float thresh);
    void setMinBlockSize(float mbs);
    void resetRelevantData(int depth, int node_count);
    float final_compression_pct;

    // set static values
    void setStatic(unsigned char* img, unsigned char* compressed_img, int error_measurement_method, float threshold, int min_size, int channel);

    // getters
    int getMaxDepth();
    int getNodeCount();
};

#endif