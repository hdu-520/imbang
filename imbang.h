//
// Created by lunaticf on 17-4-18.
//

#ifndef IMBANG_IMBANG_H
#define IMBANG_IMBANG_H

#include <vector>
#include <string>


#include "tinyxml2.h"

using namespace std;

class imbang {

public:
    void fileUnderDir(const string &dirName, int mode);

    void enhancePicByLapa(const string &dirName,const string dstDirName, int key, const string &prefix);

    void batchAlterXMLNode(const string &dirName, const string &imageDir);

    void batchAlterXMLName(const string &dirName, const string &prefix);

    void batchBlur(const string &dirName, const string &dstDirName, const string &prefix);

    void batchGaussianBlur(const string &dirName, const string &dstDirName, const string &prefix);

    void batchMedianBlur(const string &dirName, const string &dstDirName, const string &prefix);

    void batchBilateralBlur(const string &dirName, const string &dstDirName, const string &prefix);


    void enhancePicByLog(const string &dirName, const string dstDirName, const string &prefix);

    void batchSobel(const string &dirName, const string dstDirName, const string &prefix);

    void batchNoise(const string &dirName, const string dstDirName, const string &prefix, int noiseNum);

    void batchRotate(const string &dirName, const string dstDirName, const string &prefix, int degree);

    void alterXMLofRotate(const string &dirName);


    void pointThePicture(const string &xmlName, const string &imgName);


    void generateImageSets(const string &xmlName, int trainval, int train);




    /**
     *
     * @param srcDir 源文件夹路径
     * @param dstDir 目的文件夹路径
     * 将源文件夹下所有文件夹内文件复制到dstDir下
     */
    void mergeFolders(const string &srcDir,const string &dstDir);

    void ClearFilesNotFolders(const string &srcDir);

    void ClearNotUsedImgByXML(const string &img_dir,const string &xml_dir);

    void batchSharpen(const string &dirName,const string dstDirName,const string &prefix);

        void clearBarn();


private:
    vector<string> imgBarn;
    vector<string> xmlBarn;

};


#endif //IMBANG_IMBANG_H
