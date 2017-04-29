#include <iostream>
#include "imbang.h"

using namespace cv;

int main() {
    // imbang 示例数据集增强流程

    imbang bang;

    //可选步骤 可以将没用的没标的图片根据xml剔除掉 不执行也没关系
    string src = "/home/lunaticf/dataset";
    string dst = "/home/lunaticf/datasetxml";
    bang.ClearNotUsedImgByXML(src,dst);

    // src 图像目录
    // dst 生成的图像要保存的目录
    src = "/home/lunaticf/dataset";
    dst = "/home/lunaticf/newDataset/lapa4.0"; // 表示经过lapalace参数4.0的变换

    // 91为生成的图片前缀 3.5为算子参数
    bang.enhancePicByLapa(src, dst , 3.5, "91");

    // 将xml复制一份
    // 此时已生成图片 我们需要处理xml 先将原xml复制一份到下面的src
    src = "/home/lunaticf/newdataset/lapa4.0xml";
    bang.batchAlterXMLName(src,"91");
    // 修改xml的filename节点
    bang.batchAlterXMLNode(src,"91");

    // 此时lapa4.0变换已经完成，可以更改路径和函数进行其他变换
    // 最后所有操作完成后 可以将newDataSet下所有文件夹下的xml和图像合并到新路径
    src = "/home/lunaticf/newDataset";
    dst = "/home/lunaticf/finalNewDataset";
    bang.mergeFolders(src,dst);

    // 手动将xml和图片分离开 终端mv path/*.xml path即可
    // 可以根据这些xml生成测试集验证集训练集的txt
    // 假设xml路径为下
    src = "/home/lunaticf/newDatasetxml";

    // 设置训练验证集数量5000，训练集4000
    bang.generateImageSets(src,5000, 4000);

    // over.

    return 0;
}
