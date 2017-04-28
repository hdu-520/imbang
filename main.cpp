#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "imbang.h"

using namespace cv;

int main() {
    imbang bang;
    Mat image = imread("cat.jpg");
    imshow("dw",image);
    waitKey(0);


    return 0;
}
