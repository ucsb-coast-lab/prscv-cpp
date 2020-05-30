#include <iostream>
#include <string>
#include <opencv2/highgui.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "prscv.h"

using namespace std;
using namespace cv;

int main() {

    Mat img = imread("lionfish.jpeg" , CV_LOAD_IMAGE_COLOR);
    //Mat img;
    //cv::resize(orig_img, img, cv::Size(), 0.5, 0.5);
    //write_small_image_rs();
    //Mat img = imread("small_image.png",CV_LOAD_IMAGE_COLOR);
    int height = img.rows;
    int width = img.cols;
    cout << "(width,height) = (" << width << ", " << height << ")" << endl;

    // Remember, OpenCV grabs pixel in BGR format!
    int length = width * height;
    uint8_t* arr = new uint8_t[3 * height * width];
    int x, y;
    cout << " - Done with allocating memory" << endl;

    for (y = 0; y < height; y++){
        for (x = 0; x < width; x++) {
            int pixel_num = (width*y + x)*3;
            Vec3b bgr = img.at<Vec3b>(y,x); // NOTE: These arguments need to go (y,x)
            // Remember, OpenCV grabs pixel in BGR format!
            uint8_t b = bgr[0];
            uint8_t g = bgr[1];
            uint8_t r = bgr[2];
            //cout << "bgr pixel #" << pixel_num << " at (" << x << "," << y << ") : [" << to_string(b) << "," << to_string(g) << "," << to_string(r) << "]" << endl;
            *(arr + pixel_num) = b;
            *(arr + pixel_num + 1) = g;
            *(arr + pixel_num + 2) = r;
        }
    }

    // f32 transfer test, looks good
    float i = 1.0;
    float* flt_arr = new float[3];
    *(flt_arr) = 123.45;
    *(flt_arr + 1) = 67.89;
    *(flt_arr + 2) = i; 
    const float *flt_ptr;
    flt_ptr = flt_arr;
    parse_float_data(flt_ptr,3);

    // Moving onto composite structures
    xyz value = {.x = 1242, .y = 2208, .z = 123.45};
    xyz* xyz_arr = new xyz[1];
    *(xyz_arr) = value;
    const xyz *xyz_ptr;
    xyz_ptr = xyz_arr;
    parse_xyz_data(xyz_ptr,1);


    const uint8_t *ptr;
    ptr = arr;
    process_rgb_image_rs(ptr,width,height);

    // Valgrind will throw an error if we only call `delete arr` instead of `delete[] arr`
    delete[] arr; // NOTE: Always important to delete this pointer
    delete[] flt_arr;
    delete[] xyz_arr;

    return 0;
}
