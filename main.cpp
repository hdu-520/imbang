#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "imbang.h"

using namespace cv;

int main() {
    imbang bang;

    string src = "/home/lunaticf/Desktop/hehe/000531.jpg";
    string dst = "/home/lunaticf/Desktop/rotatehehe";

    Mat a = imread(src);

    cout<<a.cols<<endl<<a.rows;

    bang.batchRotate(src,dst,"36",60);

    return 0;
}
