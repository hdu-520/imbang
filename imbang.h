//
// Created by lunaticf on 17-4-18.
//

#ifndef IMBANG_IMBANG_H
#define IMBANG_IMBANG_H

#include <vector>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "tinyxml2.h"

using namespace std;
using namespace cv;

class imbang {

public:
    void myVideoToImage(string src, string dst, int step)


    void enhancePicByLapa(const string &dirName,const string dstDirName, int key, const string &prefix);

    void batchAlterXMLNode(const string &dirName, const string &imageDir);

    void batchAlterXMLName(const string &dirName, const string &prefix);

    void batchBlur(const string &dirName, const string &dstDirName, const string &prefix);

    void batchGaussianBlur(const string &dirName, const string &dstDirName, const string &prefix);

    void batchMedianBlur(const string &dirName, const string &dstDirName, const string &prefix);

    void batchBilateralBlur(const string &dirName, const string &dstDirName, const string &prefix);

    void enhancePicByLog(const string &dirName, const string dstDirName, const string &prefix);

    void batchSobel(const string &dirName, const string dstDirName, const string &prefix);

    void batchNoise(const string &src_dir,const string dst_dir,const string &prefix,int noise_num);

    void batchRotate(const string &dirName, const string dstDirName, const string &prefix, int degree);

    void alterXMLofRotate(const string &dirName);

    void pointThePicture(const string &xmlName, const string &imgName);

    void generateImageSets(const string &xmlName, int trainval, int train);

    void mergeFolders(const string &srcDir,const string &dstDir);

    void ClearFilesNotFolders(const string &srcDir);

    void ClearNotUsedImgByXML(const string &img_dir,const string &xml_dir);

    void batchSharpen(const string &dirName,const string dstDirName,const string &prefix);

    void colorReduce(const Mat &image, Mat &result, int div);


private:
    vector<string> img_barn;
    vector<string> xml_barn;

    void fileUnderDir(const string &dirName, int mode);

    void clearBarn();

};


#endif //IMBANG_IMBANG_H
