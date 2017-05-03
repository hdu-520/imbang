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


/**
 *
 * @param src 源视频路径
 * @param dst 目的存放照片路径
 * @param step 　步长
 */
void imbang::myVideoToImage(string src, string dst, int step) {
    VideoCapture capture(src);

    string imageName;
    int i = 0;

    while (1) {
        Mat frame;
        capture >> frame;
        i++;
        if (frame.empty()) {
            break;
        }
        if (i % step == 0) {
            imageName = dst + to_string(i / step) + ".jpg";
            imwrite(imageName, frame);
        }
    }
}


/**
 *
 * @param dirName 文件夹路径
 * @param mode 1为图像文件目录 2为XML文件目录
 */
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
                    img_barn.push_back(filename);
                } else {
                    xml_barn.push_back(filename);
                }
            }
        }
        closedir(dir);
    }
}

/**
 * 清除容器中已经存放的东西
 */
void imbang::clearBarn(){
    img_barn.clear();
    xml_barn.clear();
}

/**
 *
 * @param dirName 原图像目录
 * @param dstDirName 存放生成图像目录
 * @param key 拉普拉斯算子参数 建议从3.5开始 以0.5为步长
 * @param prefix 生成图像文件名前缀
 */
void imbang::enhancePicByLapa(const string &dirName,const string dstDirName, int key, const string &prefix){
    fileUnderDir(dirName,1);

    for (auto &el:img_barn) {
        string str = dirName + "/" + el;
        Mat image = imread(str);
        if (image.empty()) {
            cout << "打开图片失败,请检查" << endl;
            return;
        }
        cout << str + "    processing";
        Mat imageEnhance;
        el[0] = prefix[0];
        el[1] = prefix[1];

        Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, 0, key, 0, 0, -1, 0);
        filter2D(image, imageEnhance, CV_8UC3, kernel);

        string saveImagePath = dstDirName + "/" + el;
        imwrite(saveImagePath, imageEnhance);
        cout << endl << saveImagePath << "    saved" << endl;
    }

    clearBarn();
}

/**
 *
 * @param dirName 原图像目录
 * @param dstDirName 存放生成图像目录
 * @param prefix 生成图像文件名前缀
 * 批量进行平滑处理
 */
void imbang::batchBlur(const string &dirName,const string &dstDirName,const string &prefix){
    fileUnderDir(dirName,1);
    for(auto &el:img_barn){
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

/**
 *
 * @param dirName 原图像目录
 * @param dstDirName 存放生成图像目录
 * @param prefix 生成图像文件名前缀
 * 批量进行高斯模糊
 */
void imbang::batchGaussianBlur(const string &dirName,const string &dstDirName,const string &prefix){
    fileUnderDir(dirName,1);
    for(auto &el:img_barn){
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

/**
 *
 * @param dirName 原图像目录
 * @param dstDirName 存放生成图像目录
 * @param prefix 生成图像文件名前缀
 * 批量进行中值模糊
 */
void imbang::batchMedianBlur(const string &dirName,const string &dstDirName,const string &prefix){
    fileUnderDir(dirName,1);
    for(auto &el:img_barn){
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


/**
 *
 * @param dirName 原图像目录
 * @param dstDirName 存放生成图像目录
 * @param prefix 生成图像文件名前缀
 * 批量进行双边模糊
 */
void imbang::batchBilateralBlur(const string &dirName,const string &dstDirName,const string &prefix){
    fileUnderDir(dirName,1);
    for(auto &el:img_barn){
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


/**
 *
 * @param dirName 源文件目录
 * @param prefix 前缀
 * 根据前缀来修改对应的XML文件的filename这个节点的值
 */
void imbang::batchAlterXMLNode(const string &dirName,const string &prefix){
    fileUnderDir(dirName,2);

    for(auto &el:xml_barn){
        XMLDocument doc;
        string filePath = dirName + "/" +el;
        doc.LoadFile(filePath.c_str());

        //initialize root node
        XMLElement *RootElement = doc.RootElement();
        XMLElement *fileNameNode = RootElement->FirstChildElement()->NextSiblingElement();
        string filename = fileNameNode->GetText();
        filename[0] = prefix[0];
        filename[1] = prefix[1];
        fileNameNode->SetText(filename.c_str());
        doc.SaveFile(filePath.c_str());
        cout<<filePath<<" alter filename node done"<<endl;
    }
    clearBarn();
}

/**
 *
 * @param dirName 源文件目录
 * @param prefix 前缀
 * 根据前缀来修改对应的XML文件名
 */
void imbang::batchAlterXMLName(const string &dirName, const string &prefix){
    fileUnderDir(dirName,2);
    for(auto &el:xml_barn){
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
        for(auto &el:img_barn){
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
    for(auto &el:img_barn){
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
    for(auto &el:img_barn){
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

/**
 *
 * @param src_dir 要处理的图像文件目录
 * @param dst_dir 处理后的图片存放目录
 * @param prefix  处理后的图片要更改的前缀
 * @param noise_num  要添加的噪声数量
 *
 * 使用循环执行noise_num次，每次把随机选择的像素设置为255
 */
void imbang::batchNoise(const string &src_dir,const string dst_dir,const string &prefix,int noise_num){
    // 获取源目录的所有图像文件名
    fileUnderDir(src_dir,1);

    // 对每一张图像处理
    for(auto &el:img_barn){
        string str = src_dir + "/" + el;
        Mat image = imread(str);

        if (image.empty())
        {
            cout << "打开图片失败,请检查" << endl;
            return;
        }

        cout<<str + "    processing";

        // 更改前缀
        el[0] = prefix[0];
        el[1] = prefix[1];

        int i,j;

        for (int k = 0; k < noise_num; k++) {
            // 随机生成噪声位置
            i = rand() % image.cols;
            j = rand() % image.rows;

            // 如果图像为灰度图像
            if (image.type() == CV_8UC1) {
                image.at<uchar>(j, i) = 255;
            } else if (image.type() == CV_8UC3) {
                //图像为彩色图像 需要把三个主颜色通道都设置为255
                image.at<Vec3b>(j, i)[0] = 255;
                image.at<Vec3b>(j, i)[1] = 255;
                image.at<Vec3b>(j, i)[2] = 255;
            }
        }

        // 将修改前缀后的图像保存到指定目录
        string saveImagePath = dst_dir + "/" + el;
        imwrite(saveImagePath,image);

        cout<<endl<<saveImagePath<<"    saved"<<endl;
    }
    clearBarn();
}

void imbang::batchRotate(const string &dirName,const string dstDirName,const string &prefix, int degree){
    fileUnderDir(dirName,1);
    for(auto &el:img_barn){
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
    std::sort(xml_barn.begin(),xml_barn.end());

//    CvPoint center;
//    center.x = img.cols / 2;
//    center.y = img.rows / 2;
//
//    int i = 0;
//    for(auto &el:xml_barn){
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

    std::sort(xml_barn.begin(),xml_barn.end());
    std::sort(img_barn.begin(),img_barn.end());


    int i = 0;
    for(auto &el:xml_barn){
        XMLDocument doc;
        string filePath = xmlName + "/" +el;
        string imgPath = imgName + "/" + img_barn[i++];

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

        string imgPath1 = imgName + "/s" + img_barn[i];
        imwrite(imgPath1,Aimg);
        imshow("a",Aimg);

        waitKey(0);
        cout<<imgPath1<<"         saved"<<endl;

    }

    clearBarn();
}

/**
 *
 * @param xmlName 存放xml文件夹
 * @param trainval 需要trainval的数量
 * @param train 需要训练集的数量
 * 生成训练集测试集验证集的txt文件 test = 总数 - trainval
 */
void imbang::generateImageSets(const string &xmlName,int trainval, int train){
    // 读取
    fileUnderDir(xmlName,2);
    ofstream o;


    for(auto &el:xml_barn){
        int dotIndex = el.find(".");
        el.erase(dotIndex,el.size());
    }


    // 创建trainval.txt
    o.open(xmlName + "/trainval.txt", std::ios::out | std::ios::app);  //以写入和在文件末尾添加的方式打开.txt文件，没有的话就创建该文件。
    if (!o.is_open()) {
        return;
    }
    for(int i = 0; i < trainval; i++){
        o<<xml_barn[i]<<endl;
    }
    o.close();

    // 创建train.txt
    o.open(xmlName + "/train.txt", std::ios::out | std::ios::app);  //以写入和在文件末尾添加的方式打开.txt文件，没有的话就创建该文件。
    if (!o.is_open()) {
        return;
    }
    // 写入指定的train张图片
    for(int i = 0; i < train; i++){
        o<<xml_barn[i]<<endl;
    }
    o.close();

    // 创建val.txt
    o.open(xmlName + "/val.txt", std::ios::out | std::ios::app);  //以写入和在文件末尾添加的方式打开.txt文件，没有的话就创建该文件。
    if (!o.is_open()) {
        return;
    }
    // 写入train后的val张图片 总和为trainval
    for(int i = train; i < trainval; i++){
        o<<xml_barn[i]<<endl;
    }
    o.close();

    // 创建test.txt
    o.open(xmlName + "/test.txt", std::ios::out | std::ios::app);  //以写入和在文件末尾添加的方式打开.txt文件，没有的话就创建该文件。
    if (!o.is_open()) {
        return;
    }
    // 把最后剩下的图片当作测试集
    for(int i = trainval; i < xml_barn.size(); i++){
        o<<xml_barn[i]<<endl;
    }
    o.close();
    clearBarn();
}

/**
 *
 * @param srcDir 源文件夹
 * @param dstDir 目的文件夹
 * 合并一个文件夹下所有文件夹下文件到另一个文件夹
 */
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


/**
 *
 * @param srcDir 源文件
 * 清除一个文件夹下所有文件夹的文件
 */
void imbang::ClearFilesNotFolders(const string &srcDir) {
    fileUnderDir(srcDir,1);

    string cmd = "";

    for(auto &el:img_barn)
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

/**
 *
 * @param img_dir 图像文件目录
 * @param xml_dir xml文件目录
 * 标定时有的图像会没有目标物而不标 此函数可以根据xml去除那些没用的图像
 */
void imbang::ClearNotUsedImgByXML(const string &img_dir,const string &xml_dir) {
    fileUnderDir(img_dir,1);
    fileUnderDir(xml_dir,2);

    for(auto &el:xml_barn){
        int dotIndex = el.find(".");
        el.erase(dotIndex,el.size());
    }



    for(auto &el:img_barn){
        int dotIndex = el.find(".");
        el.erase(dotIndex,el.size());
    }

    string cmd = "";

    for(auto &el:img_barn)
    {
        bool flag = false;
        for(auto &xml:xml_barn){
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


/**
 *
 * @param image 输入图像
 * @param result 输出图像
 * @param div 减色因子
 * 减色算法
 * 如果需要就地处理图像，可以在输入和输出参数中用同一个image变量colorReduce(image,image)
 */
void imbang::colorReduce(const Mat &image, Mat &result, int div = 64){
    // 构建一个大小与类型都与输入图像相同的矩阵
    result.create(image.rows, image.cols, image.type());

    int n1 = image.rows; // 行数
    int nc = image.cols * image.channels(); // 每行的元素数量
    for(int j = 0; j < n1; j++) {
        const uchar* data_in = image.ptr<uchar>(j);
        uchar* data_out = result.ptr<uchar>(j);

        for(int i = 0; i < nc; i++) {
            // 处理每个像素
            data_out[i] = data_in[i]/div*div + div/2;
        }// 一行结束
    }
}















