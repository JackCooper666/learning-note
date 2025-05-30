#include<iostream>
using namespace std;

// int main() {
//     int a = 10;
//     int b = 10;
//     cout << ++a << endl; 
//     // Pre-increment: increments a, then returns the value of a
//     cout << a << endl; 
//     // Outputs the incremented value of a
//     cout << b++ << endl; 
//     // Post-increment: returns the value of b, then increments b
//     cout << b << endl; 
//     // Outputs the incremented value of b
// }

class Mydecrement {
    public:
    int m_A;
    Mydecrement(int a){
        m_A = a;
    }
    //前置--
    Mydecrement& operator--() {
        m_A--;
        return *this; // 返回当前对象的引用
    }
    //后置--
    Mydecrement operator--(int) {
        Mydecrement temp = *this; // 保存当前对象的状态
        m_A--; // 执行减法操作
        return temp; // 返回保存的状态
    }
};

ostream& operator<<(ostream& cout, const Mydecrement& my) {
    cout << my.m_A;
    return cout; // 返回输出流
}

void test01() {
    Mydecrement my(10);
    cout << --my << endl; // 前置--
    cout << my << endl; // 输出当前值
    cout << my-- << endl; // 后置--
    cout << my << endl; // 输出当前值
}
int main() {
    test01();
    return EXIT_SUCCESS;
}