```cpp
#include <flann/flann.hpp>
using namespace flann;
/**
* flann_test_data 包含了一个我已经处理好的点云文件
* 定义如下：
* float cloud_data[89*3] ={...};
*/
#include "flann_test_data.h"

int main(int argc, char const *argv[])
{
    // 点云数据输入，第一个参数是存放点云的指针，第二个89表示有89个点，第三个3表示点是三维的{x,y,z}
    Matrix<float> datasets(cloud_data,89,3);
    // 查询的点，我这里，是把第91个点作为查找的点，
    //第一个查询点的起始位置指针，第二个1表示查询一个点，第三个3表示查询的点是三维的
    Matrix<float> query(cloud_data+90,1,3);
    // 查询nn个最近点
    int nn = 10;
    // 查询的结果，索引存放的位置
    Matrix<int> indices(new int[query.rows*nn], query.rows, nn);
    // 对应的距离
    Matrix<float> dists(new float[query.rows*nn], query.rows, nn); 
    // L2_3D：起始就是一个类用来计算三维点之间的距离
    // datasets：点云数据
    // flann::KDTreeSingleIndexParams(15)：根据这个参数，构建树时会构建KDTreeSingleIndex，叶子节点为15
    Index<L2_3D<float>> index(datasets,flann::KDTreeSingleIndexParams(15));
    // 树的构建，构建算法就是在这儿执行
    index.buildIndex();
    // 最近邻搜索
    index.knnSearch(query, indices, dists, nn, flann::SearchParams (-1 ,0.0));
    // 输出
    for (size_t i = 0; i < dists.cols; i++)
    {
       std::cout<<dists[0][i]<<" index: "<<indices[0][i]<<std::endl;
    }
    
    return 0;
}
/**
* 如果是PCL的点云的话，就转换成flann的matrix就可以了，这个也很简单，写个for拷贝就行了
*/

```