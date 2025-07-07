refer to 
CSDN博主「hongge_smile」的原创文章，遵循CC 4.0 BY-SA版权协议
原文链接：https://blog.csdn.net/hongge_smile/article/details/107296658
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
    cout << m.block<2, 2>(1, 1) << endl << endl;      // m.block<i,j> (a,b) 表示从第(a+1)行(b+1)列开始,截图i行,j列
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
注意:m.block<i,j> (a,b) 表示从第(a+1)行(b+1)列开始,截图i行,j列
m.block(a,b,i,j) 表示从第(a+1)行(b+1)列开始,截图i行,j列

上述例子中的块操作方法作为表达式的右值，意味着是只读形式的，然而，块操作也可以作为左值使用，意味着你可以给他赋值。下面的例子说明了这一点，当然对于矩阵的操作是一样的。
```cpp
//
// Created by fuhong on 20-7-14.
//

#include <Eigen/Dense>
#include <iostream>

using namespace std;
using namespace Eigen;

int main() {
    Array22f m;
    m << 1, 2,
            3, 4;
    Array44f a = Array44f::Constant(0.6);
    cout << "Here is the array a:" << endl << a << endl << endl;
    a.block<2, 2>(1, 1) = m;
    cout << "Here is now a with m copied into its central 2x2 block:" << endl << a << endl << endl;
    a.block(0, 0, 2, 3) = a.block(2, 1, 2, 3);
    cout << "Here is now a with bottom-right 2x3 block copied into top-left 2x2 block:" << endl << a << endl << endl;
}

```

```bash
Here is the array a:
0.6 0.6 0.6 0.6
0.6 0.6 0.6 0.6
0.6 0.6 0.6 0.6
0.6 0.6 0.6 0.6

Here is now a with m copied into its central 2x2 block:
0.6 0.6 0.6 0.6
0.6   1   2 0.6
0.6   3   4 0.6
0.6 0.6 0.6 0.6

Here is now a with bottom-right 2x3 block copied into top-left 2x2 block:
  3   4 0.6 0.6
0.6 0.6 0.6 0.6
0.6   3   4 0.6
0.6 0.6 0.6 0.6

```

## 10.2行和列(cols and rows)

行和列是一中特殊的块。Eigen提供了特殊的方法：col() 列 row() 行。
```cpp
//
// Created by fuhong on 20-7-14.
//


#include <Eigen/Dense>
#include <iostream>

using namespace std;

int main() {
    Eigen::MatrixXf m(4, 4);
    // 数组初始化
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m(i, j) = j + 1 + i * 4;
        }
    }
    cout << "Here is the matrix m:" << endl << m << endl;
    cout << "2nd Row: " << m.row(1) << endl;
    m.col(2) += 3 * m.col(0);
    cout << "After adding 3 times the first column into the third column, the matrix m is:\n";
    cout << m << endl;
}
```
输出:
```bash
Here is the matrix m:
 1  2  3  4
 5  6  7  8
 9 10 11 12
13 14 15 16
2nd Row: 5 6 7 8
After adding 3 times the first column into the third column, the matrix m is:
 1  2  6  4
 5  6 22  8
 9 10 38 12
13 14 54 16
```

## 10.3 边角相关的操作

Eigen同样提供了对于挨着矩阵或数组的边、角的特殊操作方法，比如topLeftCorner()方法可用于操作矩阵左上角的区域。总结如下：
![[eigen_block_corner.png]]
```cpp
//
// Created by fuhong on 20-7-14.
//


#include <Eigen/Dense>
#include <iostream>

using namespace std;

int main() {
    Eigen::Matrix4f m;
    m << 1, 2, 3, 4,
            5, 6, 7, 8,
            9, 10, 11, 12,
            13, 14, 15, 16;
    cout << "m.leftCols(2) =" << endl << m.leftCols(2) << endl << endl;
    cout << "m.bottomRows<2>() =" << endl << m.bottomRows<2>() << endl << endl;
    m.topLeftCorner(1, 3) = m.bottomRightCorner(3, 1).transpose();
    cout << "After assignment, m = " << endl << m << endl;
}

```
输出:
```bash
m.leftCols(2) =
 1  2
 5  6
 9 10
13 14

m.bottomRows<2>() =
 9 10 11 12
13 14 15 16

After assignment, m = 
 8 12 16  4
 5  6  7  8
 9 10 11 12
13 14 15 16

```

## 10.4 对于向量的块操作

Eigen也提供了一些针对向量和一维数组的块操作方法：
![[eigen_block_vector.png]]
```cpp
//
// Created by fuhong on 20-7-14.
//

#include <Eigen/Dense>
#include <iostream>
using namespace std;
int main()
{
    Eigen::ArrayXf v(6);
    v << 1, 2, 3, 4, 5, 6;
    cout << "v.head(3) =" << endl << v.head(3) << endl << endl;
    cout << "v.tail<3>() = " << endl << v.tail<3>() << endl << endl;
    v.segment(1,4) *= 2;
    cout << "after 'v.segment(1,4) *= 2', v =" << endl << v << endl;
}

```

输出:
```bash
v.head(3) =
1
2
3

v.tail<3>() = 
4
5
6

after 'v.segment(1,4) *= 2', v =
 1
 4
 6
 8
10
 6

```

# 11 范数计算
范数是一个把向量或矩阵映射为非负实数的函数，表示其“长度”或“大小”。
设 $\mathbf{x} \in \mathbb{R}^n$，则一个函数 $\|\cdot\|: \mathbb{R}^n \to \mathbb{R}$ 是范数，需要满足以下 3 条性质：
1. **非负性**：$||\mathbf{x}\| \geq 0$，且当且仅当 $\mathbf{x} = 0$ 时取等号。
2. **齐次性（正比例）**：$\|\alpha \mathbf{x}\| = |\alpha| \cdot \|\mathbf{x}\|$
3. **三角不等式**：$\|\mathbf{x} + \mathbf{y}\| \leq \|\mathbf{x}\| + \|\mathbf{y}\|$

| 名称       |     | 记号                        |     | 公式                    | 描述         |
| -------- | --- | ------------------------- | --- | --------------------- | ---------- |
| L1 范数    |     | $\|\mathbf{x}\|\\_1$      |     | $\sum_i$              | x_i        |
| L2 范数    |     | $\|\mathbf{x}\|\\_2$      |     | $\sqrt{\sum_i x_i^2}$ | 欧几里得距离（常用） |
| 无穷范数     |     | $\|\mathbf{x}\|\\_\infty$ |     | $\max_i$              | x_i        |
| 零范数（伪范数） |     | $\|\mathbf{x}\|_0$        |     | 非零元素个数（不是范数）          | 用于稀疏性建模    |

向量的平方范数由squaredNorm()获得，等价于向量对自身做点积，也等同于所有元素额平方和。Eigen也提供了norm()范数，返回的是squaredNorm()的根。这些操作也适用于矩阵。如果想使用其他元素级的范数，使用lpNorm

()方法，当求无穷范数时，模板参数p可以取特殊值Infinity，得到的是所有元素的最大绝对值。
```cpp
//
// Created by fuhong on 20-7-14.
//

#include <Eigen/Dense>
#include <iostream>

using namespace std;
using namespace Eigen;

int main() {
    VectorXf v(2);
    MatrixXf m(2, 2), n(2, 2);

    v << -1, 2;

    m << 1, -2, -3, 4;
    cout << "v.squaredNorm() = " << v.squaredNorm() << endl;
    cout << "v.norm() = " << v.norm() << endl;
    cout << "v.lpNorm<1>() = " << v.lpNorm<1>() << endl;
    cout << "v.lpNorm<Infinity>() = " << v.lpNorm<Infinity>() << endl;
    cout << endl;
    cout << "m.squaredNorm() = " << m.squaredNorm() << endl;
    cout << "m.norm() = " << m.norm() << endl;
    cout << "m.lpNorm<1>() = " << m.lpNorm<1>() << endl;
    cout << "m.lpNorm<Infinity>() = " << m.lpNorm<Infinity>() << endl;
}

```

输出:
```bash
v.squaredNorm() = 5
v.norm() = 2.23607
v.lpNorm<1>() = 3
v.lpNorm<Infinity>() = 2

m.squaredNorm() = 30
m.norm() = 5.47723
m.lpNorm<1>() = 10
m.lpNorm<Infinity>() = 4

```

矩阵的1范数和无穷范数也可以用下面的方法计算：
```cpp
#include <Eigen/Dense>
#include <iostream>
using namespace Eigen;
using namespace std;
int main()
{
  MatrixXf m(2,2);
  m << 1,-2,
       -3,4;
  cout << "1-norm(m)     = " << m.cwiseAbs().colwise().sum().maxCoeff()
       << " == "             << m.colwise().lpNorm<1>().maxCoeff() << endl;
  cout << "infty-norm(m) = " << m.cwiseAbs().rowwise().sum().maxCoeff()
       << " == "             << m.rowwise().lpNorm<1>().maxCoeff() << endl;
}

```
输出:
```bash
1-norm(m)     = 6 == 6
infty-norm(m) = 7 == 7

```
### 1. `v.squaredNorm()`
- **定义**：向量的 **平方范数**，即所有元素平方后再求和（不取平方根）。
- **公式**：
    $\text{squaredNorm} = \sum_{i} v_i^2$​
- **示例**：  
    对于 `v = [-1, 2]`，
    $\text{squaredNorm} = (-1)^2 + 2^2 = 1 + 4 = 5$

---

### 2. `v.norm()`

- **定义**：向量的 **欧几里得范数**（也叫 L2 范数），是向量长度。
- **公式**：
    $\text{norm} = \sqrt{\sum_i v_i^2}$
- **示例**：
    $\text{norm} = \sqrt{5} \approx 2.236$

---

### 3. `v.lpNorm<1>()`

- **定义**：向量的 **L1 范数**，也称曼哈顿距离，是所有元素绝对值之和。
- **公式**：
    $\text{L1 norm} = \sum_i |v_i|$
- **示例**：
	- $|-1| + |2| = 1 + 2 = 3$

---

### 4. `v.lpNorm<Infinity>()`

- **定义**：**无穷范数**，是向量中绝对值最大的元素。
- **公式**：
    $\text{Infinity norm} = \max_i |v_i|$
- **示例**：
    $\max(|-1|, |2|) = 2$

---

### 对于矩阵 `m`

Eigen 也定义了矩阵的这些范数，它们一般是**将矩阵视为向量**后进行计算：

---

### 5. `m.squaredNorm()`
- 把矩阵展平为一个向量后计算平方和：
    $1^2 + (-2)^2 + (-3)^2 + 4^2 = 1 + 4 + 9 + 16 = 30$

---

### 6. `m.norm()`

- 相当于：
    $\sqrt{m.squaredNorm()} = \sqrt{30} \approx 5.477$

---

### 7. `m.lpNorm<1>()`

- 是**矩阵中所有元素的绝对值之和**：
    $|1| + |−2| + |−3| + |4| = 1 + 2 + 3 + 4 = 10$

---

### 8. `m.lpNorm<Infinity>()`

- 是矩阵中**元素绝对值的最大值**：
    $\max(|1|, |−2|, |−3|, |4|) = 4$

---
# 12 布尔规约

如下的操作得到的是布尔值
all()返回真，如果矩阵或数组的所有元素为真
any()返回真，如果矩阵或数组至少有一个元素为真
count()返回元素为真的个数
```cpp
#include <Eigen/Dense>
#include <iostream>
using namespace std;
using namespace Eigen;
int main()
{
  ArrayXXf a(2,2);
  
  a << 1,2,
       3,4;
  cout << "(a > 0).all()   = " << (a > 0).all() << endl;
  cout << "(a > 0).any()   = " << (a > 0).any() << endl;
  cout << "(a > 0).count() = " << (a > 0).count() << endl;
  cout << endl;
  cout << "(a > 2).all()   = " << (a > 2).all() << endl;
  cout << "(a > 2).any()   = " << (a > 2).any() << endl;
  cout << "(a > 2).count() = " << (a > 2).count() << endl;
}
```


输出:
```bash
(a > 0).all()   = 1
(a > 0).any()   = 1
(a > 0).count() = 4

(a > 2).all()   = 0
(a > 2).any()   = 1
(a > 2).count() = 2
```
# 13迭代

当需要获得元素在矩阵或数组中的位置时使用迭代。
```cpp
#include <iostream>
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;
int main()
{
  Eigen::MatrixXf m(2,2);
  
  m << 1, 2,
       3, 4;
  //get location of maximum
  MatrixXf::Index maxRow, maxCol;
  float max = m.maxCoeff(&maxRow, &maxCol);
  //get location of minimum
  MatrixXf::Index minRow, minCol;
  float min = m.minCoeff(&minRow, &minCol);
  cout << "Max: " << max <<  ", at: " <<
     maxRow << "," << maxCol << endl;
  cout << "Min: " << min << ", at: " <<
     minRow << "," << minCol << endl;
}
```
输出:
```bash
Max: 4, at: 1,1
Min: 1, at: 0,0
```

# 14 部分规约

部分规约指的是对矩阵或数组按行或列进行的操作，对每一列或者行进行规约操作时得到的是一个列或者行向量。如下例子得到矩阵每一列的最大值并存入一个行向量中
```cpp
#include <iostream>
#include <Eigen/Dense>
using namespace std;
int main()
{
  Eigen::MatrixXf mat(2,4);
  mat << 1, 2, 6, 9,
         3, 1, 7, 2;
  
  std::cout << "Column's maximum: " << std::endl
   << mat.colwise().maxCoeff() << std::endl;
}
```

输出：
```bash
Column's maximum: 
3 2 7 9
```
同样也可以得到每一行的最大值，返回一个列向量
```cpp
#include <iostream>
#include <Eigen/Dense>
using namespace std;
int main()
{
  Eigen::MatrixXf mat(2,4);
  mat << 1, 2, 6, 9,
         3, 1, 7, 2;
  
  std::cout << "Row's maximum: " << std::endl
   << mat.rowwise().maxCoeff() << std::endl;
}
```

输出:
```bash
Row's maximum: 
9
7
```

部分规约和其他操作的结合
使用部分规约操作得到的结果去做其他的操作也是可以的，如下例子用于得到矩阵中元素和最大的一列
```cpp
#include <iostream>
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;
int main()
{
  MatrixXf mat(2,4);
  mat << 1, 2, 6, 9,
         3, 1, 7, 2;
  
  MatrixXf::Index   maxIndex;
  float maxNorm = mat.colwise().sum().maxCoeff(&maxIndex);
  
  std::cout << "Maximum sum at position " << maxIndex << std::endl;
  std::cout << "The corresponding vector is: " << std::endl;
  std::cout << mat.col( maxIndex ) << std::endl;
  std::cout << "And its sum is is: " << maxNorm << std::endl;
}

```

输出:
```bash
Maximum sum at position 2
The corresponding vector is: 
6
7
And its sum is is: 13
```

通过colwise()迭代，应用sum()对每一列规约操作得到一个新的1x4的矩阵，因此如果
在这里插入图片描述
那么,
在这里插入图片描述
最终执行maxCoeff()操作获得元素和最大的列的索引。
# 15 广播机制

广播的概念类似于部分规约，不同之处在于广播通过对向量在一个方向上的复制，将向量解释成矩阵。如下例子将一个列向量加到矩阵的每一列中
```cpp
#include <iostream>
#include <Eigen/Dense>
using namespace std;
int main()
{
  Eigen::MatrixXf mat(2,4);
  Eigen::VectorXf v(2);
  
  mat << 1, 2, 6, 9,
         3, 1, 7, 2;
         
  v << 0,
       1;
       
  //add v to each column of m
  mat.colwise() += v;
  
  std::cout << "Broadcasting result: " << std::endl;
  std::cout << mat << std::endl;
}

```

输出:
```bash
Broadcasting result: 
1 2 6 9
4 2 8 3

```

可以将mat.colwise()+=v理解成两种等价的方式，它将列向量加到矩阵的每一列中；或者将列向量复制4次的得到一个2x4的矩阵，之后进行矩阵的相加运算：

+=、+和-运算符也可以按列或行操作。在数组中也可以用*=、/=、和/运算符执行元素级的按行或列乘除运算。但不能用在矩阵上，如果想用v(0)乘以矩阵的第0列，v(1)乘以矩阵的第1列…使用mat = mat*v.asDiagonal()。
结合广播和其他操作

广播也可以和其他操作结合，比如矩阵或数组的运算、规约和部分规约操作。下面介绍一个更加复杂的例子，演示了在矩阵中找到和给定向量最接近的一列，使用到了欧氏距离。
```cpp
#include <iostream>
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;
int main()
{
  Eigen::MatrixXf m(2,4);
  Eigen::VectorXf v(2);
  
  m << 1, 23, 6, 9,
       3, 11, 7, 2;
       
  v << 2,
       3;
  MatrixXf::Index index;
  // find nearest neighbour
  (m.colwise() - v).colwise().squaredNorm().minCoeff(&index);
  cout << "Nearest neighbour is column " << index << ":" << endl;
  cout << m.col(index) << endl;
}
```

输出:
```bash
Nearest neighbour is column 0:
1
3
```
其中
(m.colwise() - v).colwise().squaredNorm().minCoeff(&index);
这句话做的工作是：

（1）m.colwise()-v是一个广播操作，矩阵m的每一列减去v，得到一个新的矩阵

在这里插入图片描述
（2）(m.colwise() - v).colwise().squareNorm()是部分规约操作，按列计算矩阵的平方范数，得到一个行向量
在这里插入图片描述
（3）最终minCoeff(&index)根据欧氏距离获得矩阵中最接近v的一列的索引。
16几何模块的实践(Geometry)

详细说明参考官网:点我
Eigen的几何模块用来表达空间的旋转、平移等变换。3维空间中刚体的运动有六个自由度，分别是绕3个轴的旋转运动和沿着3个轴的平移运动。对于旋转可以用3x3的旋转矩阵R表示，旋转矩阵描述了刚体经过矩阵作用后的姿态信息，旋转矩阵是一个正交矩阵；然而旋转矩阵有9个参数，9个参数描述6自由度的旋转，有点冗余了。因此旋转还可以用旋转向量来表示，空间中物体的旋转可以看作是绕这某个轴转过一定的角度完成，因此旋转矩阵是个3维向量，其方向代表转轴的方向，其大小代表旋转的角度。

实际中物体不光有旋转，还有平移运动，如果用t表示平移向量，那么R*p+t可以描述刚体p的旋转加平移运动，然而当连续多次运动时整个表达式将会变得非常复杂，比如R1*(R*p+t)+t1描述连续两次的运动，因此为了简化书写形式引入齐次坐标的概念，将坐标扩充到4维，将旋转矩阵和平移向量写入一个4x4的变换矩阵中，简化了连续运动公式的形式，但是结果是16个参数描述一个6自由度的运动，更加冗余了。在旋转向量的后面增加3维代表平移向量，即用6维的旋转向量描述旋转和平移运动，看起来比较紧凑了，但是像欧拉角一样也会遇到万向锁问题，导致奇异性；最终即不冗余又紧凑又没有万向锁问题的解决方案是使用四元数描述旋转问题，这也是很多飞控代码中用到的方案。
```cpp
// Created by 开机烫手 on 2018/4/8.
#include <iostream>
#include <Eigen/Dense>
#include <cmath>
#include <Eigen/Geometry>
#include <Eigen/Core>
 
using namespace std;
using namespace Eigen;
 
int main() {
 
    // 旋转矩阵直接用Matrix3d即可
    Matrix3d rotation_matrix;
    rotation_matrix.setIdentity();
    // 旋转向量 由旋转轴和旋转角度组成
    AngleAxisd rotation_vector(M_PI / 4, Vector3d(0, 0, 1));
    cout.precision(3);
    cout << "rotation vector: Angle is: " << rotation_vector.angle() * (180 / M_PI)
         << "  Axis is: " << rotation_vector.axis().transpose() << endl;
    cout << "rotation matrix =\n" << rotation_vector.matrix() << endl;
    rotation_matrix = rotation_vector.toRotationMatrix();
    // 下面v是待旋转的向量，或者认为空间中的一个刚体的位置
    Vector3d v(1, 0, 0);
    Vector3d v_rotated = rotation_vector * v;
    cout << "(1,0,0) after rotation = " << v_rotated.transpose() << endl;
    v_rotated = rotation_matrix * v;
    cout << "(1,0,0) after rotation = " << v_rotated.transpose() << endl;
 
    // 欧拉角 按ZYX的顺序 由旋转矩阵直接转换成欧拉角
    Vector3d euler_angles = rotation_matrix.eulerAngles(2, 1, 0);
    cout << "yaw pitch roll = " << euler_angles.transpose() * (180 / M_PI) << endl;
 
    // 变换矩阵  4x4的
    Isometry3d T = Eigen::Isometry3d::Identity();
    T.rotate(rotation_vector);
//    T.rotate(rotation_matrix);    // 这样写也行，相当于由旋转矩阵构造变换矩阵
    // 设置平移向量
    T.pretranslate(Eigen::Vector3d(0, 0, 3));
    cout << "Transform matrix = \n" << T.matrix() << endl;
 
    // 用变换矩阵进行坐标变换
    Vector3d v_transformed = T * v;
    cout << "v transformed = " << v_transformed.transpose() << endl;
 
    // 由旋转向量构造四元数
    Quaterniond q = Eigen::Quaterniond(rotation_vector);
    cout << "quaternion = \n" << q.coeffs() << endl;
    // 由旋转矩阵构造四元数
    q = Eigen::Quaterniond(rotation_matrix);
    cout << "quaternion = \n" << q.coeffs() << endl;
    v_rotated = q * v;
    cout << "(1,0,0) after rotation = " << v_rotated.transpose() << endl;
 
    return 0;
}

```

输出:
```bash
rotation vector: Angle is: 45  Axis is: 0 0 1
rotation matrix =
 0.707 -0.707      0
 0.707  0.707      0
     0      0      1
(1,0,0) after rotation = 0.707 0.707     0
(1,0,0) after rotation = 0.707 0.707     0
yaw pitch roll = 45 -0  0
Transform matrix =
 0.707 -0.707      0      0
 0.707  0.707      0      0
     0      0      1      3
     0      0      0      1
v transformed = 0.707 0.707     3
quaternion =
    0
    0
0.383
0.924
quaternion =
    0
    0
0.383
0.924
(1,0,0) after rotation = 0.707 0.707     0
```

17 稠密问题之线性代数和分解

官网: http://eigen.tuxfamily.org/dox/group__DenseLinearSolvers__chapter.html
参考链接: https://blog.csdn.net/u012936940/article/details/79871941
