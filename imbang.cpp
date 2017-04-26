//
// Created by lunaticf on 17-4-18.
//


#include <iostream>
#include <dirent.h>
#include <string>
#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <fstream>

#include "imbang.h"
#include "tinyxml2.h"

using namespace std;
using namespace cv;
using namespace tinyxml2;

void imbang::fileUnderDir(const string &dirName, int mode){
    // open specific dir
    DIR* dir = opendir(dirName.c_str());
    if(dir == NULL){
        cout<<dirName<<"  The dir not exist!";
    } else {
        dirent* p = NULL;

        while((p = readdir(dir)) != NULL)
        {
            if(p->d_name[0] != '.')
            {
                string filename = string(p->d_name);
                if(mode == 1){
                    imgBarn.push_back(filename);
                } else {
                    xmlBarn.push_back(filename);
                }
            }
        }
        closedir(dir);
    }
}


void imbang::clearBarn(){
    imgBarn.clear();
    xmlBarn.clear();
}

void imbang::enhancePicByLapa(const string &dirName,const string dstDirName, int key, const string &prefix){
    fileUnderDir(dirName,1);
        for(auto &el:imgBarn){
            string str = dirName + "/" + el;
            Mat image = imread(str);
            if (image.empty())
            {
                cout << "打开图片失败,请检查" << endl;
                return;
            }
            cout<<str + "    processing";
            Mat imageEnhance;
            el[0] = prefix[0];
            el[1] = prefix[1];

            Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, 0, key, 0, 0, -1, 0);
            filter2D(image, imageEnhance, CV_8UC3, kernel);
            string saveImagePath = dstDirName + "/" + el;
            imwrite(saveImagePath,imageEnhance);
            cout<<endl<<saveImagePath<<"    saved"<<endl;
        }
    clearBarn();
}

void imbang::batchBlur(const string &dirName,const string &dstDirName,const string &prefix){
    fileUnderDir(dirName,1);
    for(auto &el:imgBarn){
        string str = dirName + "/" + el;
            Mat image = imread(str);
            if (image.empty())
            {
                cout << "打开图片失败,请检查" << endl;
                return;
            }
            cout<<str + "    processing";
            el[0] = prefix[0];
            el[1] = prefix[1];
            Mat bluredImg;
            blur( image,bluredImg, Size( 7, 7), Point(-1,-1) );


            string saveImagePath = dstDirName + "/" + el;
            imwrite(saveImagePath,bluredImg);
            cout<<endl<<saveImagePath<<"    saved"<<endl;
    }
    clearBarn();
}


void imbang::batchGaussianBlur(const string &dirName,const string &dstDirName,const string &prefix){
    fileUnderDir(dirName,1);
    for(auto &el:imgBarn){
        string str = dirName + "/" + el;
        Mat image = imread(str);
        if (image.empty())
        {
            cout << "打开图片失败,请检查" << endl;
            return;
        }
        cout<<str + "    processing";
        el[0] = prefix[0];
        el[1] = prefix[1];
        Mat bluredImg;
        GaussianBlur( image,bluredImg, Size( 5, 5),0,0);


        string saveImagePath = dstDirName + "/" + el;
        imwrite(saveImagePath,bluredImg);
        cout<<endl<<saveImagePath<<"    saved"<<endl;
    }
    clearBarn();
}

void imbang::batchMedianBlur(const string &dirName,const string &dstDirName,const string &prefix){
    fileUnderDir(dirName,1);
    for(auto &el:imgBarn){
        string str = dirName + "/" + el;
        Mat image = imread(str);
        if (image.empty())
        {
            cout << "打开图片失败,请检查" << endl;
            return;
        }
        cout<<str + "    processing";
        el[0] = prefix[0];
        el[1] = prefix[1];
        Mat bluredImg;
        medianBlur( image,bluredImg,7);


        string saveImagePath = dstDirName + "/" + el;
        imwrite(saveImagePath,bluredImg);
        cout<<endl<<saveImagePath<<"    saved"<<endl;
    }
    clearBarn();
}


void imbang::batchBilateralBlur(const string &dirName,const string &dstDirName,const string &prefix){
    fileUnderDir(dirName,1);
    for(auto &el:imgBarn){
        string str = dirName + "/" + el;
        Mat image = imread(str);
        if (image.empty())
        {
            cout << "打开图片失败,请检查" << endl;
            return;
        }
        cout<<str + "    processing";
        el[0] = prefix[0];
        el[1] = prefix[1];
        Mat bluredImg;
        bilateralFilter(image,bluredImg, 25, 25*2, 25/2);


        string saveImagePath = dstDirName + "/" + el;
        imwrite(saveImagePath,bluredImg);
        cout<<endl<<saveImagePath<<"    saved"<<endl;
    }
    clearBarn();
}




void imbang::batchAlterXMLNode(const string &dirName,const string &imageDir){
    fileUnderDir(imageDir,1);
    fileUnderDir(dirName,2);
    std::sort(xmlBarn.begin(),xmlBarn.end());
    std::sort(imgBarn.begin(),imgBarn.end());


    int i = 0;
    for(auto &el:xmlBarn){
        XMLDocument doc;
        string filePath = dirName + "/" +el;
        doc.LoadFile(filePath.c_str());

        //initialize root node
        XMLElement *RootElement = doc.RootElement();
        XMLElement *fileNameNode = RootElement->FirstChildElement()->NextSiblingElement();
        fileNameNode->SetText((imgBarn[i++]).c_str());
        doc.SaveFile(filePath.c_str());
        cout<<filePath<<" alter filename node done"<<endl;
    }
    clearBarn();
}

void imbang::batchAlterXMLName(const string &dirName, const string &prefix){
    fileUnderDir(dirName,2);
    for(auto &el:xmlBarn){
        string filePath = dirName + "/" + el;
        el[0] = prefix[0];
        el[1] = prefix[1];
        string toFilePath = dirName + "/" + el;
        rename(filePath.c_str(),toFilePath.c_str());
        cout<<toFilePath<<"          rename successful!"<<endl;
    }

    clearBarn();

}


void imbang::enhancePicByLog(const string &dirName,const string dstDirName,const string &prefix){
    fileUnderDir(dirName,1);
        for(auto &el:imgBarn){
            string str = dirName + "/" + el;
            Mat image = imread(str);
            if (image.empty())
            {
                cout << "打开图片失败,请检查" << endl;
                return;
            }
            cout<<str + "    processing";
            el[0] = prefix[0];
            el[1] = prefix[1];

            Mat imageLog(image.size(), CV_32FC3);
            for (int i = 0; i < image.rows; i++)
            {
                for (int j = 0; j < image.cols; j++)
                {
                    imageLog.at<Vec3f>(i, j)[0] = log(1 + image.at<Vec3b>(i, j)[0]);
                    imageLog.at<Vec3f>(i, j)[1] = log(1 + image.at<Vec3b>(i, j)[1]);
                    imageLog.at<Vec3f>(i, j)[2] = log(1 + image.at<Vec3b>(i, j)[2]);
                }
            }
            //归一化到0~255
            normalize(imageLog, imageLog, 0, 255, CV_MINMAX);

            //转换成8bit图像显示
            convertScaleAbs(imageLog, imageLog);
            string saveImagePath = dstDirName + "/" + el;
            imwrite(saveImagePath,imageLog);
            cout<<endl<<saveImagePath<<"    saved"<<endl;
        }
    clearBarn();
}

void imbang::batchSobel(const string &dirName,const string dstDirName,const string &prefix){
    fileUnderDir(dirName,1);
    Mat grad_x,grad_y;
    Mat abs_grad_x,abs_grad_y,dst;
    for(auto &el:imgBarn){
        string str = dirName + "/" + el;
        Mat image = imread(str);
        if (image.empty())
        {
            cout << "打开图片失败,请检查" << endl;
            return;
        }
        cout<<str + "    processing";
        el[0] = prefix[0];
        el[1] = prefix[1];

        Sobel(image, grad_x,CV_16S,1,0,3,1,1,BORDER_DEFAULT);
        convertScaleAbs(grad_x,abs_grad_x);

        Sobel(image, grad_y,CV_16S,0,1,3,1,1,BORDER_DEFAULT);
        convertScaleAbs(grad_y,abs_grad_y);

        addWeighted(abs_grad_x,0.5,abs_grad_y,0.5,0,dst);

        string saveImagePath = dstDirName + "/" + el;
        imwrite(saveImagePath,dst);

        cout<<endl<<saveImagePath<<"    saved"<<endl;
    }
    clearBarn();
}


void imbang::batchSharpen(const string &dirName,const string dstDirName,const string &prefix){
    fileUnderDir(dirName,1);
    for(auto &el:imgBarn){
        string str = dirName + "/" + el;
        Mat img = imread(str);
        if (img.empty())
        {
            cout << "打开图片失败,请检查" << endl;
            return;
        }
        cout<<str + "    processing";
        el[0] = prefix[0];
        el[1] = prefix[1];

        Mat result;

        //创建一张空白图片
        result.create(img.size(), img.type());
        //处理边界内部的像素点, 图像最外围的像素点应该额外处理
        for (int row = 1; row < img.rows - 1; row++)
        {
            //前一行像素点
            const uchar* previous = img.ptr<const uchar>(row - 1);
            //待处理的当前行
            const uchar* current = img.ptr<const uchar>(row);
            //下一行像素点
            const uchar* next = img.ptr<const uchar>(row + 1);
            uchar *output = result.ptr<uchar>(row);
            int ch = img.channels();
            int starts = ch;
            int ends = (img.cols - 1) * ch;
            for (int col = starts; col < ends; col++)
            {
                //输出图像的遍历指针与当前行的指针同步递增, 以每行的每一个像素点的每一个通道值为一个递增量, 因为要考虑到图像的通道数
                *output++ = saturate_cast<uchar>(5 * current[col] - current[col - ch] - current[col + ch] - previous[col] - next[col]);
            }
        } //end loop

        //处理边界, 外围像素点设为 0
        result.row(0).setTo(Scalar::all(0));
        result.row(result.rows - 1).setTo(Scalar::all(0));
        result.col(0).setTo(Scalar::all(0));
        result.col(result.cols - 1).setTo(Scalar::all(0));




        string saveImagePath = dstDirName + "/" + el;
        imwrite(saveImagePath,result);

        cout<<endl<<saveImagePath<<"    saved"<<endl;
    }
    clearBarn();
}

void imbang::batchNoise(const string &dirName,const string dstDirName,const string &prefix,int noiseNum){
    fileUnderDir(dirName,1);

    for(auto &el:imgBarn){
        string str = dirName + "/" + el;
        Mat image = imread(str);
        if (image.empty())
        {
            cout << "打开图片失败,请检查" << endl;
            return;
        }
        cout<<str + "    processing";
        el[0] = prefix[0];
        el[1] = prefix[1];

            for(int k=0;k<noiseNum;k++)
            {
                int i=rand()%image.cols;
                int j=rand()%image.rows;
                if(image.channels()==1)
                {
                    image.at<uchar>(j,i)=255;
                }
                else if(image.channels()==3)
                {
                    image.at<Vec3b>(j,i)[0]=255;
                    image.at<Vec3b>(j,i)[1]=255;
                    image.at<Vec3b>(j,i)[2]=255;
                }
            }

        string saveImagePath = dstDirName + "/" + el;
        imwrite(saveImagePath,image);

        cout<<endl<<saveImagePath<<"    saved"<<endl;
    }
    clearBarn();
}

void imbang::batchRotate(const string &dirName,const string dstDirName,const string &prefix, int degree){
    fileUnderDir(dirName,1);
    for(auto &el:imgBarn){
        string str = dirName + "/" + el;
        Mat image = imread(str);
        if (image.empty())
        {
            cout << "打开图片失败,请检查" << endl;
            return;
        }
        cout<<str + "    processing";
        el[0] = prefix[0];
        el[1] = prefix[1];

        double angle = degree * CV_PI / 180.; // 旋转角度
        double a = sin(angle), b = cos(angle);
        int width = image.cols;
        int height = image.rows;
        int width_rotate = int(height * fabs(a) + width * fabs(b));
        int height_rotate = int(width * fabs(a) + height * fabs(b));

        //生成仿射变换矩阵
        float map[6];
        Mat map_matrix = Mat(2, 3, CV_32F, map);
        CvPoint2D32f center = cvPoint2D32f(width / 2, height / 2);
        CvMat map_matrix2 = map_matrix;
        cv2DRotationMatrix(center, degree, 1.0, &map_matrix2);
        map[2] += (width_rotate - width) / 2;
        map[5] += (height_rotate - height) / 2;

        Mat img_rotate;
        float *tmp = (float *)map_matrix.data;
        warpAffine(image, img_rotate, map_matrix, Size(width_rotate, height_rotate), 1, 0, 0);	//仿射变换函数


        string saveImagePath = dstDirName + "/" + el;
        imwrite(saveImagePath,img_rotate);

        cout<<endl<<saveImagePath<<"    saved"<<endl;
    }
    clearBarn();
}

void imbang::alterXMLofRotate(const string &dirName) {
    fileUnderDir(dirName,2);
    std::sort(xmlBarn.begin(),xmlBarn.end());

//    CvPoint center;
//    center.x = img.cols / 2;
//    center.y = img.rows / 2;
//
//    int i = 0;
//    for(auto &el:xmlBarn){
//        XMLDocument doc;
//        string filePath = dirName + "/" +el;
//        // read a xml
//        doc.LoadFile(filePath.c_str());
//
//        //initialize root node
//        XMLElement *RootElement = doc.RootElement();
//
//        XMLElement *locationNode = RootElement->FirstChildElement("object");
//        while(locationNode){
//            XMLElement *bndBox = locationNode->FirstChildElement("bndbox");
//
//            XMLElement *xmin = bndBox->FirstChildElement("xmin");
//            XMLElement *ymin = bndBox->FirstChildElement("ymin");
//            XMLElement *xmax = bndBox->FirstChildElement("xmax");
//            XMLElement *ymax = bndBox->FirstChildElement("ymax");
//
//            double oldxmin = atof(xmin->GetText());
//            double oldymin = atof(ymin->GetText());
//            double oldxmax = atof(xmax->GetText());
//            double oldymax = atof(ymax->GetText());
//
//
//
//
//            int newxmin = oldxmin * varyData[0] + oldymin * varyData[1] + varyData[2];
//            int newymin = oldxmin * varyData[3] + oldymin * varyData[4] + varyData[5];
//            int newxmax = (oldxmax) * varyData[0] + (oldymax) * varyData[1] + varyData[2];
//            int newymax = (oldxmax) * varyData[3] + (oldymax) * varyData[4] + varyData[5];
//
//
//
//            xmin->SetText(newxmin);
//            ymin->SetText(newymin);
//            xmax->SetText(newxmax);
//            ymax->SetText(newymax);
//
//            locationNode = locationNode->NextSiblingElement("object");
//        }
//
//        doc.SaveFile(filePath.c_str());
//        cout<<filePath<<"           saved "<<endl;
//    }

    clearBarn();
}


void imbang::pointThePicture(const string &xmlName,const string &imgName) {
    fileUnderDir(xmlName,2);
    fileUnderDir(imgName,1);

    std::sort(xmlBarn.begin(),xmlBarn.end());
    std::sort(imgBarn.begin(),imgBarn.end());


    int i = 0;
    for(auto &el:xmlBarn){
        XMLDocument doc;
        string filePath = xmlName + "/" +el;
        string imgPath = imgName + "/" + imgBarn[i++];

        Mat Aimg  = imread(imgPath);

        Point center(Aimg.cols/2.0, Aimg.rows/2.0);



        // read a xml
        doc.LoadFile(filePath.c_str());

        //initialize root node
        XMLElement *RootElement = doc.RootElement();

        XMLElement *locationNode = RootElement->FirstChildElement("object");
        while(locationNode){
            XMLElement *bndBox = locationNode->FirstChildElement("bndbox");

            XMLElement *xmin = bndBox->FirstChildElement("xmin");
            XMLElement *ymin = bndBox->FirstChildElement("ymin");
            XMLElement *xmax = bndBox->FirstChildElement("xmax");
            XMLElement *ymax = bndBox->FirstChildElement("ymax");



            int oldxmin = atoi(xmin->GetText());
            int oldymin = atoi(ymin->GetText());
            int oldxmax = atoi(xmax->GetText());
            int oldymax = atoi(ymax->GetText());




            Point dsta, dstb;
            int x1 = oldxmin - center.x;
            int y1 = oldymin - center.y;

            double angle=60*CV_PI/180;

            dsta.x = cvRound(x1 * cos(angle) + y1 * sin(angle) + center.x);
            dsta.y = cvRound(-x1 * sin(angle) + y1 * cos(angle) + center.y);

            int x2 = oldxmax - center.x;
            int y2 = oldymax - center.y;

            dstb.x = cvRound(x2 * cos(angle) + y2 * sin(angle) + center.x);
            dstb.y = cvRound(-x2 * sin(angle) + y2 * cos(angle) + center.y);




            rectangle(Aimg,dsta,dstb,Scalar(0,0,255),3,8,0);
            imshow("a",Aimg);

            waitKey(0);

            locationNode = locationNode->NextSiblingElement("object");
        }

        string imgPath1 = imgName + "/s" + imgBarn[i];
        imwrite(imgPath1,Aimg);
        imshow("a",Aimg);

        waitKey(0);
        cout<<imgPath1<<"         saved"<<endl;

    }

    clearBarn();
}


void imbang::generateImageSets(const string &xmlName,int trainval, int train){
    // 读取
    fileUnderDir(xmlName,2);
    ofstream o;


    for(auto &el:xmlBarn){
        int dotIndex = el.find(".");
        el.erase(dotIndex,el.size());
    }


    // 创建trainval.txt
    o.open(xmlName + "/trainval.txt", std::ios::out | std::ios::app);  //以写入和在文件末尾添加的方式打开.txt文件，没有的话就创建该文件。
    if (!o.is_open()) {
        return;
    }
    for(int i = 0; i < trainval; i++){
        o<<xmlBarn[i]<<endl;
    }
    o.close();

    // 创建train.txt
    o.open(xmlName + "/train.txt", std::ios::out | std::ios::app);  //以写入和在文件末尾添加的方式打开.txt文件，没有的话就创建该文件。
    if (!o.is_open()) {
        return;
    }
    // 写入指定的train张图片
    for(int i = 0; i < train; i++){
        o<<xmlBarn[i]<<endl;
    }
    o.close();

    // 创建val.txt
    o.open(xmlName + "/val.txt", std::ios::out | std::ios::app);  //以写入和在文件末尾添加的方式打开.txt文件，没有的话就创建该文件。
    if (!o.is_open()) {
        return;
    }
    // 写入train后的val张图片 总和为trainval
    for(int i = train; i < trainval; i++){
        o<<xmlBarn[i]<<endl;
    }
    o.close();

    // 创建test.txt
    o.open(xmlName + "/test.txt", std::ios::out | std::ios::app);  //以写入和在文件末尾添加的方式打开.txt文件，没有的话就创建该文件。
    if (!o.is_open()) {
        return;
    }
    // 把最后剩下的图片当作测试集
    for(int i = trainval; i < xmlBarn.size(); i++){
        o<<xmlBarn[i]<<endl;
    }
    o.close();
    clearBarn();
}


void imbang::mergeFolders(const string &srcDir, const string &dstDir) {
    string path=srcDir;
    vector<string> files;//存放文件名
    DIR *dir;
    struct dirent *ptr;
    char base[1000];
    string temp;
    string cmd="";


    const char *b =path.c_str();

    if ((dir=opendir(b)) == NULL)
    {
        perror("Open dir error...");
        exit(1);
    }

    while ((ptr=readdir(dir)) != NULL)
    {
        if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0)    ///current dir OR parrent dir
            continue;
        else if(ptr->d_type == 8)    ///file
        {
            //printf("d_name:%s/%s\n",basePath,ptr->d_name);
            temp=ptr->d_name;
            cmd = "cp "+ srcDir +"/" + temp + " "+ dstDir;
            system(cmd.c_str());
        }
        else if(ptr->d_type == 10)    ///link file
            //printf("d_name:%s/%s\n",basePath,ptr->d_name);
            continue;
        else if(ptr->d_type == 4)    ///dir
        {
            temp=ptr->d_name;
            files.push_back(temp);
        }
    }
    closedir(dir);
    cmd = "";

    for(int i=0; i<files.size(); i++)
    {
        //cout<<files[i]<<endl;
        cmd+="cp "+ srcDir + "/";
        cmd+=files[i];
        cmd+="/* ";
        cmd+=dstDir;

        system(cmd.c_str());
        cmd="";
    }
}



void imbang::ClearFilesNotFolders(const string &srcDir) {
    fileUnderDir(srcDir,1);

    string cmd = "";

    for(auto &el:imgBarn)
    {
        //cout<<files[i]<<endl;
        cmd+="rm -rf "+ srcDir + "/";
        cmd+= el;
        cmd+="/* ";

        system(cmd.c_str());
        cmd="";
    }
    clearBarn();
}

void imbang::ClearNotUsedImgByXML(const string &img_dir,const string &xml_dir) {
    fileUnderDir(img_dir,1);
    fileUnderDir(xml_dir,2);

    for(auto &el:xmlBarn){
        int dotIndex = el.find(".");
        el.erase(dotIndex,el.size());
    }



    for(auto &el:imgBarn){
        int dotIndex = el.find(".");
        el.erase(dotIndex,el.size());
    }

    string cmd = "";

    for(auto &el:imgBarn)
    {
        bool flag = false;
        for(auto &xml:xmlBarn){
            if(xml == el){
                flag = true;
            }
        }
        if(!flag){
            cmd += "rm -rf "+ img_dir + "/";
            cmd +=  el;
            cmd += ".jpg ";

            system(cmd.c_str());
            cout<<cmd<<endl;
            cmd="";
        }
    }

    clearBarn();
}

// 获取指定像素点放射变换后的新的坐标位置
CvPoint getPointAffinedPos(const CvPoint &src, const CvPoint &center, double angle)
{
    CvPoint dst;
    int x = src.x - center.x;
    int y = src.y - center.y;

    dst.x = cvRound(x * cos(angle) + y * sin(angle) + center.x);
    dst.y = cvRound(-x * sin(angle) + y * cos(angle) + center.y);
    return dst;
}















