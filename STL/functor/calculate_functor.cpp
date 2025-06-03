#include <iostream>
#include <string>
#include <functional> // this is the functor library
using namespace std;

void test01() {
    //加法仿函数
    plus<int> p;
    cout << p(10,20) << endl;

}

void test02() {
    //取反仿函数
    negate<int> n;
    cout << n(50) << endl;
}

int main (){
    test01();
    test02();
    return 0;
}