# 1.Eigen安装及使用

## 1.1 安装

eigen3在linux下的安装可以直接用命令安装：
```bash
sudo apt-get install libeigen3-dev
```
## 1.2 CMakeLists.txt编写

eigen库采用模板编程技术，仅由一些头文件组成，运行速度快。用cmake管理项目的时候，只需要在CMakeLists.txt里面头文件的路径即可：
```Cmake
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})
```
## 1.3 版本查看

终端输入命令：
```bash
tac /usr/include/eigen3/Eigen/src/Core/util/Macros.h    # tac表示从文本的后面往前输出，
```
## 1.4 Eigen每个头文件的作用

[模块和头文件详细介绍](http://eigen.tuxfamily.org/dox/group__QuickRefPage.html#QuickRef_Types)  
Eigen所有的头文件及头文件里面的类的作用见下表：
一般为了省事，可以直接导入#include <Eigen/Dense> 或者#include <Eigen/Eigen>
![[eigen_lib.png]]
# 2.Eigen使用基础

## 2.1 Eigen入门-hello Eigen

先来一个最简单的eigen程序体验下：
```cpp
#include <iostream>
#include <Eigen/Dense>    // Eigen头文件，<Eigen/Dense>包含Eigen库里面所有的函数和类
 
int main()
{
  Eigen::MatrixXd m(2,2);   // MatrixXd 表示的是动态数组，初始化的时候指定数组的行数和列数
  m(0,0) = 3;               //m(i,j) 表示第i行第j列的值，这里对数组进行初始化
  m(1,0) = 2.5;
  m(0,1) = -1;
  m(1,1) = m(1,0) + m(0,1);
  std::cout << m << std::endl;     // eigen重载了<<运算符，可以直接输出eigen矩阵的值
}

```
输出：
```bash
  3  -1
2.5 1.5
```

## 2.2 Matrices and vectors
```cpp
//
// Created by fuhong on 20-7-12.
//

#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

int main() {
    MatrixXd m = MatrixXd::Random(3, 3);            //初始化动态矩阵m,使用Random函数,初始化的值在[-1,1]区间内,矩阵大小3X3
    m = (m + MatrixXd::Constant(3, 3, 1.2)) * 50;   // MatrixXd::Constant(3, 3, 1.2)初始化3X3矩阵,矩阵里面的数值为常量,全部为1.2
    // Eigen重载了+ 运算符，两个矩阵有相同的行数和列数即可相加,对应位置上的值相加
    cout << "m =" << endl << m << endl;
    VectorXd v(3);
    v << 1, 2, 3;                                   //逗号初始化，英文：comma-initializer,Eigen未提供c++11 的{}初始化方式
    cout << "m * v =" << endl << m * v << endl;
}

```
输出：
```bash
m =
94.0188  89.844 43.5223
49.4383 101.165  86.823
88.3099 29.7551 37.7775
m * v =
404.274
512.237
261.153
```
