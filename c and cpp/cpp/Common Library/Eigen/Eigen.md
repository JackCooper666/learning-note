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
# 3.Eigen使用基础

## 3.1 Eigen入门-hello Eigen

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

## 3.2 Matrices and vectors
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
## 3.3 逗号初始化 comma-initializer

关于Eigen逗号初始化的说明见文档：
Eigen逗号初始化
下面是逗号初始化的简单说明：
Eigen提供了一种逗号初始化器语法，该语法使用户可以轻松设置矩阵，向量或数组的所有系数。只需列出系数，从左上角开始，从左到右，从上到下移动。需要预先指定对象的大小。如果列出的系数太少或太多，编译器就会报错。
此外，初始化列表的元素本身可以是向量或矩阵。通常的用途是将向量或矩阵连接在一起。例如，这是如何将两个行向量连接在一起。请记住，必须先设置大小，然后才能使用逗号初始化程序。
```cpp
RowVectorXd vec1(3);
vec1 << 1, 2, 3;
std::cout << "vec1 = " << vec1 << std::endl;
 
RowVectorXd vec2(4);
vec2 << 1, 4, 9, 16;
std::cout << "vec2 = " << vec2 << std::endl;
 
RowVectorXd joined(7);
joined << vec1, vec2;
std::cout << "joined = " << joined << std::endl;
```
## 3.4 一些常用的初始化方法(初始化为0，初始化为1，初始化为单位矩阵)
```cpp
//
// Created by fuhong on 20-7-12.
//

#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

int main() {
    MatrixXd m0 = MatrixXd::Random(3, 3);           //随机初始化初始化的值在[-1,1]区间内,矩阵大小3X3
    MatrixXd m1 = MatrixXd::Constant(3, 3, 2.4);    //常量值初始化,矩阵里面的值全部为2.4 ,三个参数分别代表：行数，列数，常量值
    Matrix2d m2 = Matrix2d::Zero();                 //零初始化.矩阵里面的值全部为0
    Matrix3d m3 = Matrix3d::Ones();                 // 矩阵里面的值全部初始化为1
    Matrix4d m4 = Matrix4d::Identity();             //初始化为单位矩阵
    Matrix3d m5;                                    //逗号初始化
    m5 << 1, 2, 3, 4, 5, 6, 7, 8, 9;
    cout << "m0 =" << endl << m0 << endl;
    cout << "m1 =" << endl << m1 << endl;
    cout << "m2 =" << endl << m2 << endl;
    cout << "m3 =" << endl << m3 << endl;
    cout << "m4 =" << endl << m4 << endl;
    cout << "m5 =" << endl << m5 << endl;


    MatrixXf mat = MatrixXf::Ones(2, 3);
    std::cout << "before: " << endl << mat << std::endl << std::endl;
    mat = (MatrixXf(2, 2) << 0, 1, 2, 0).finished() * mat;    //此处使用了临时变量，然后使用逗号初始化，在此必须使用finish（）方法来获取实际的矩阵对象。
    std::cout << "after: " << endl << mat << std::endl;
}
```

```bash
m0 =
 0.680375   0.59688 -0.329554
-0.211234  0.823295  0.536459
 0.566198 -0.604897 -0.444451
m1 =
2.4 2.4 2.4
2.4 2.4 2.4
2.4 2.4 2.4
m2 =
0 0
0 0
m3 =
1 1 1
1 1 1
1 1 1
m4 =
1 0 0 0
0 1 0 0
0 0 1 0
0 0 0 1
m5 =
1 2 3
4 5 6
7 8 9
before: 
1 1 1
1 1 1

after: 
1 1 1
2 2 2
```

## 3.5 调整矩阵大小

矩阵的当前大小可以通过rows（），cols（）和size（）检索。这些方法分别返回行数，列数和系数数。调整动态大小矩阵的大小是通过resize（）方法完成的。  
动态矩阵可以随意调整矩阵大小，固定尺寸的矩阵无法调整大小。
```cpp
//
// Created by fuhong on 20-7-13.
//

#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;

int main() {
    MatrixXd m(2, 5);
    m.resize(4, 3);
    std::cout << "The matrix m is of size "
              << m.rows() << "x" << m.cols() << std::endl;
    std::cout << "It has " << m.size() << " coefficients" << std::endl;
    VectorXd v(2);
    v.resize(5);
    std::cout << "The vector v is of size " << v.size() << std::endl;
    std::cout << "As a matrix, v is of size "
              << v.rows() << "x" << v.cols() << std::endl;
}

```
```bash
The matrix m is of size 4x3
It has 12 coefficients
The vector v is of size 5
As a matrix, v is of size 5x1
```

## 3.6 固定尺寸与动态尺寸的选择(Fixed vs. Dynamic size)

什么时候应该使用固定尺寸（例如Matrix4f），什么时候应该使用动态尺寸（例如MatrixXf）？简单的答案是：在可能的地方使用固定尺寸来显示非常小的尺寸，在需要的地方使用动态尺寸来显示较大的尺寸。对于小尺寸，尤其是对于小于（大约）16的尺寸，使用固定尺寸对性能有极大的好处，因为它使Eigen避免了动态内存分配并展开了循环。在内部，固定大小的本征矩阵只是一个简单的数组，即
`Matrix4f mymatrix;`
等同于： `float mymatrix[16];`
因此，这确实具有零运行时间成本。相比之下，动态大小矩阵的数组始终分配在堆上，因此
`MatrixXf mymatrix(rows,columns);`
等同于： `float mymatrix = new float[rowscolumns];`
# 4.矩阵类(The Matrix class)

在Eigen中，所有matrices和vectors都是Matrix模板类的对象。vectors只是matrices的一种特殊情况，具有1行或1列。
## 4.1 Matrix的前三个模板参数

该矩阵类需要六个模板参数，但一般只需了解前三个参数即可。剩下的三个参数具有默认值，现在我们将保持不变，下面将进行讨论。关于后面三个参数的详细解释见：点我

Matrix的三个必需模板参数是：
Matrix<typename Scalar, int RowsAtCompileTime, int ColsAtCompileTime>
Scalar 是标量类型，即系数的类型。也就是说，如果要使用浮点数矩阵，请在此处选择float。有关所有受支持的标量类型的列表以及如何将支持扩展到新类型的信息，请参见标量类型。
RowsAtCompileTime和ColsAtCompileTime是在编译时已知的矩阵的行数和列数（如果在编译时不知道该数，该怎么办）请参见下文。
我们提供了许多方便的typedef来覆盖通常的情况。例如，Matrix4f是一个4x4的浮点矩阵。这是Eigen定义的：
```cpp
typedef Matrix<float, 3, 1> Vector3f;
typedef Matrix<int, 1, 2> RowVector2i;
typedef Matrix<double, Dynamic, Dynamic> MatrixXd;
typedef Matrix<int, Dynamic, 1> VectorXi;

typedef Array<float,Dynamic,Dynamic>       ArrayXXf
typedef Array<double,Dynamic,1>            ArrayXd
typedef Array<int,1,Dynamic>               RowArrayXi
typedef Array<float,3,3>                   Array33f
typedef Array<float,4,1>                   Array4f
```

## 4.2 vectors

在Eigen中，vectors只是Matrix的一种特殊情况，具有1行或1列。他们只有1列的情况最为常见；这样的向量称为列向量，通常缩写为向量。在另一行有1行的情况下，它们称为行向量。
`typedef Matrix <float，3，1> Vector3f;`
## 4.3 动态矩阵

动态矩阵在编译的时候不知道其大小，需要在运行的时候才能确定其大小。  
`typedef Matrix <double，Dynamic，Dynamic> MatrixXd; ` 
例如我们可以这样定义一个动态矩阵：
```cpp
MatrixXd m(3,4) ;  // 指定矩阵大小为3X4，也可以不指定
```
# 5.Array类的介绍

Eigen 不仅提供了Matrix和Vector结构，还提供了Array结构。区别如下，Matrix和Vector就是线性代数中定义的矩阵和向量，所有的数学运算都和数学上一致。但是存在一个问题是数学上的定义并不一定能完全满足现实需求。比如，数学上并没有定义一个矩阵和一个标量的加法运算。但是如果我们想给一个矩阵的每个元素都加上同一个数，那么这个操作就需要我们自己去实现，这显然并不方便。
Array 提供了一个Array类，为我们提供了大量的矩阵未定义的操作，且Array和Matrix之间很容易相互转换 ，所以相当于给矩阵提供更多的方法。也为使用者的不同需求提供了更多的选择。

下面看一下Array类的实现。Array类和Matrix有相同的参数。

`Array<typename Scalar, int RowsAtCompileTime , int ColsAtCompileTime >`

上面参数的意义和Matrix中参数的意义是相同的。

Array也对常用的情况作了一些类型定义。
```cpp
typedef Array<float ,Dynamic,1> ArrayXf;
typedef Array<float,3,1> Array3f;

typedef Array<double,Dynamic ,Dynamic > ArrayXXd;
typedef Array<double ,3,3 > Array33d;
```

## 5.1 Array初始化，加减乘除操作

Eigen::Array类重载了+ ， - ，* ,/ 运算符，可以直接用这些运算符对Array对象进行操作。相乘操作是对应的数字相乘，相除是对应的元素相除。
```cpp
//
// Created by fuhong on 20-7-13.
//

#include <iostream>
#include <eigen3/Eigen/Dense>

using namespace Eigen;
using namespace std;

int main(int argc, char **argv) {
    ArrayXXf a(3, 3);
    ArrayXXf b(3, 3);
    a << 1, 2, 3,
            4, 5, 6,
            7, 8, 9;
    b << 1, 2, 3,
            1, 2, 3,
            1, 2, 3;
    cout << "a + b = " << endl << a + b << endl << endl;
    cout << "a - 2 = " << endl << a - 2 << endl;
    cout << "a * b = " << endl << a * b << endl;
    cout << "a / b = " << endl << a / b << endl;

    return 0;
}
```
输出如下：
```cpp
a + b = 
 2  4  6
 5  7  9
 8 10 12

a - 2 = 
-1 0 1
2 3 4
5 6 7
a * b = 
 1  4  9
 4 10 18
 7 16 27
a / b = 
  1   1   1
  4 2.5   2
  7   4   3
```
## 5.2 Array类的其他操作

Array 还定义了 绝对值 abs() ，开平方根sqrt() , 以及找对应元素最小值操作 min() ;
```cpp
//
// Created by fuhong on 20-7-13.
//
#include <iostream>
#include <eigen3/Eigen/Dense>

using namespace Eigen;
using namespace std;

int main(int argc, char **argv) {
    ArrayXXf a = ArrayXXf::Random(2,2);     // 初始化2X2  Array
    a *= 2;
    cout << "a = " << endl
         << a << endl;
    cout << "a.abs() = " << endl
         << a.abs() << endl;
    cout << "a.abs().sqrt() =" << endl
         << a.abs().sqrt() << endl;
    cout << "a.min(a.abs().sqrt()) = " << endl
         << a.min(a.abs().sqrt()) << endl;
    return 0;
}
```
输出：
```bash
a = 
1.36075  1.1324
-0.422468 1.19376
a.abs() = 
1.36075  1.1324
0.422468 1.19376
a.abs().sqrt() =
1.16651 1.06414
0.649976 1.09259
a.min(a.abs().sqrt()) = 
1.16651 1.06414
-0.422468 1.09259

```
Array 和 Matrix 之间可以方便地进行转换。

Array 有 `.matrix( )` 方法。  
Matrix 有 `.array( )`方法。详细用法见下一小节。

# 6.Matrix和Array之间的相互转换

Matrix类和Array类之间可以相互转换，必须显式转换，才能对他们进行加减乘除运算。
```cpp
//
// Created by fuhong on 20-7-13.
//

#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;

int main() {
    Array44f a1, a2;
    Matrix4f m1, m2;
    m1 = a1 * a2;                     // coeffwise乘积，从数组到矩阵的隐式转换。
    a1 = m1 * m2;                     //矩阵乘积，从矩阵到数组的隐式转换。
    a2 = a1 + m1.array();             //禁止混合数组和矩阵，必须显式转换以后才可以相加
    m2 = a1.matrix() + m1;            //，并且需要显式转换。
    ArrayWrapper<Matrix4f> m1a(m1);   // m1a是m1.array（）的别名，它们共享相同的系数
    MatrixWrapper<Array44f> a1m(a1);

    std::cout << "a1: " << std::endl << a1 << std::endl;
    std::cout << "a2: " << std::endl << a2 << std::endl;
    std::cout << "m1: " << std::endl << m1 << std::endl;
    std::cout << "m2: " << std::endl << m2 << std::endl;
}
```

# 7 矩阵转置，共轭，共轭转置

下面介绍矩阵的一些操作：

## 7.1 转置和共轭

对矩阵的转置、共轭和共轭转置由成员函数transpose(),conjugate(),adjoint()实现
```cpp

MatrixXcf a = MatrixXcf::Random(2,2);
cout << "Here is the matrix a\n" << a << endl;
cout << "Here is the matrix a^T\n" << a.transpose() << endl;
cout << "Here is the conjugate of a\n" << a.conjugate() << endl;
cout << "Here is the matrix a^*\n" << a.adjoint() << endl;

```
输出：
```bash
Here is the matrix a
 (-0.211,0.68) (-0.605,0.823)
 (0.597,0.566)  (0.536,-0.33)
Here is the matrix a^T
 (-0.211,0.68)  (0.597,0.566)
(-0.605,0.823)  (0.536,-0.33)
Here is the conjugate of a
 (-0.211,-0.68) (-0.605,-0.823)
 (0.597,-0.566)    (0.536,0.33)
Here is the matrix a^*
 (-0.211,-0.68)  (0.597,-0.566)
(-0.605,-0.823)    (0.536,0.33)

```

## 7.2转置需要注意的事项
在Eigen库中，`.transpose()` 不能直接用于原地转置（即不能写成 `a = a.transpose();`）
```cpp
//
// Created by fuhong on 20-7-13.
//
#include <iostream>
#include <eigen3/Eigen/Dense>

using namespace Eigen;
using namespace std;

int main(int argc, char **argv) {
    Matrix2i a;
    a << 1, 2, 3, 4;
    cout << "Here is the matrix a:\n" << a << endl;
//    a = a.transpose(); // !!! do NOT do this !!!       不要这样写代码，无法运行
    a.transposeInPlace();

    cout << "and the result of the aliasing effect:\n" << a << endl;
    return 0;
}

```
输出：
```bash
Here is the matrix a:
1 2
3 4
and the result of the aliasing effect:
1 3
2 4

```
# 8 点积和叉积

对于点积和叉积，直接使用dot()和cross()方法
```cpp

#include <iostream>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;
int main()
{
  Vector3d v(1,2,3);
  Vector3d w(0,1,2);
  cout << "Dot product: " << v.dot(w) << endl;
  double dp = v.adjoint()*w; // automatic conversion of the inner product to a scalar
  cout << "Dot product via a matrix product: " << dp << endl;
  cout << "Cross product:\n" << v.cross(w) << endl;
}
```
输出：
```bash
Dot product: 8
Dot product via a matrix product: 8
Cross product:
 1
-2
 1
```
**注意：记住叉积仅仅用于尺寸为3的向量！点积可以用于任意尺寸的向量，当使用复数时，Eigen的点积操作是第一个变量为共轭线性的，第二个为线性的。**

# 9 矩阵的基础的算术(求和,平均值等)

Eigen提供了一些对于矩阵或向量的规约操作，如sum(),prod(),maxCoeff()和minCoeff()
```cpp
#include <iostream>
#include <Eigen/Dense>
using namespace std;
int main()
{
  Eigen::Matrix2d mat;
  mat << 1, 2,
         3, 4;
  cout << "Here is mat.sum():       " << mat.sum()       << endl;
  cout << "Here is mat.prod():      " << mat.prod()      << endl;
  cout << "Here is mat.mean():      " << mat.mean()      << endl;
  cout << "Here is mat.minCoeff():  " << mat.minCoeff()  << endl;
  cout << "Here is mat.maxCoeff():  " << mat.maxCoeff()  << endl;
  cout << "Here is mat.trace():     " << mat.trace()     << endl;
}

```
输出：
```bash
Here is mat.sum():       10
Here is mat.prod():      24
Here is mat.mean():      2.5
Here is mat.minCoeff():  1
Here is mat.maxCoeff():  4
Here is mat.trace():     5
```
trace为矩阵的迹，也可以由a.diagonal().sum()得到。  
minCoeff和maxCoeff函数也可以返回相应的元素的位置信息

```cpp

Matrix3f m = Matrix3f::Random();
  std::ptrdiff_t i, j;
  float minOfM = m.minCoeff(&i,&j);
  cout << "Here is the matrix m:\n" << m << endl;
  cout << "Its minimum coefficient (" << minOfM 
       << ") is at position (" << i << "," << j << ")\n\n";
  RowVector4i v = RowVector4i::Random();
  int maxOfV = v.maxCoeff(&i);
  cout << "Here is the vector v: " << v << endl;
  cout << "Its maximum coefficient (" << maxOfV 
       << ") is at position " << i << endl;

```

输出：
```bash
Here is the matrix m:
  0.68  0.597  -0.33
-0.211  0.823  0.536
 0.566 -0.605 -0.444
Its minimum coefficient (-0.605) is at position (2,1)

Here is the vector v:  1  0  3 -3
Its maximum coefficient (3) is at position 2

```
# 10 Eigen 块操作

## 10.1块基本操作

块指的是矩阵或数组中的一个矩形区域，块表达式可以用于左值或者右值，同样不会耗费运行时间，由编译器优化。  
Eigen中最常用的块操作是block()方法，共有两个版本
![[eigen_block.png]]
索引从0开始。两个版本都可用于固定尺寸或者动态尺寸的矩阵和数组。这两个表达式语义上相同，唯一的区别是如果块的尺寸比较小的话固定尺寸版本的块操作运行更快，但是需要在编译阶段知道大小。
```cpp
//
// Created by fuhong on 20-7-14.
//


#include <Eigen/Dense>
#include <iostream>

using namespace std;

int main() {
    Eigen::MatrixXf m(4, 4);
    // 初始化m矩阵
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m(i, j) = j + 1 + i * 4;
        }
    }
    cout << "m: " << endl << m << endl;
    cout << "Block in the middle" << endl;
    cout << m.block<2, 2>(1, 1) << endl << endl;      // m.block<i,j> (a,b) 表示从第(a+1)行(b+1)列开始,截图1行,1列
    for (int i = 1; i <= 3; ++i) {
        cout << "Block of size " << i << "x" << i << endl;
        cout << m.block(0, 0, i, i) << endl << endl;  //m.block(a,b,i,j) 表示从第(a+1)行(b+1)列开始,截图i行,j列
    }
}
```
输出:
```bash
m: 
 1  2  3  4
 5  6  7  8
 9 10 11 12
13 14 15 16
Block in the middle
 6  7
10 11

Block of size 1x1
1

Block of size 2x2
1 2
5 6

Block of size 3x3
 1  2  3
 5  6  7
 9 10 11

```