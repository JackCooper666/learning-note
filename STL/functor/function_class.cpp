#include <iostream>
#include <string>
using namespace std;
/*
the function class is used to overload the operator()
*/
//1、函数对象在使用时，可以像普通函数那样调用, 可以有参数，可以有返回值
class MyAdd {
    public:
    MyAdd(int a, int b){
        m_a = a;
        m_b = b;
    }
    int operator()(int v1, int v2){
        return v1 + v2;
    }

    int m_a;
    int m_b;
};

void test01(){
    MyAdd myadd(20,30);
    cout << myadd(10,20) << endl;
}

//2、函数对象可以有自己的状态
class MyPrint {
    public:
    MyPrint()
    {
        count = 0;
    }

    void operator()(string name){
        cout << name << endl;
        count++;
    }

    int count;
};

void test02(){
    MyPrint myprint;
    myprint("hello world");
    myprint("hello world");
    myprint("hello world");
    myprint("hello world");
    cout << myprint.count << endl;

}

//3、函数对象可以作为参数传递
void doPrint(MyPrint &mp, string name)
{
    mp(name);
    mp(name);
    mp(name);
    mp(name);
}

void test03(){
    MyPrint mp;
    doPrint(mp,"hello world");
    cout << mp.count << endl;
}

int main(){
    cout << "---------------------------" << endl;
    test01();
    cout << "---------------------------" << endl;
    test02();
    cout << "---------------------------" << endl;
    test03();
    return 0;
}