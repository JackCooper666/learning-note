#include<iostream>
#include<string>
using namespace std;

class Base1 {
    public:
    Base1() {
        cout << "Base1 constructor called" << endl;
        m_A = 10;
        m_B = 20; // duplicate member m_B from Base1, Base2 and Son
    }
    ~Base1() {
        cout << "Base1 destructor called" << endl;
    }
    int m_A;
    int m_B;    
};

class Base2 {
    public:
    Base2() {
        cout << "Base2 constructor called" << endl;
        m_B = 30; // duplicate member m_B from Base1, Base2 and Son
        m_C = 40;
    }
    ~Base2() {
        cout << "Base2 destructor called" << endl;
    }
    int m_B;
    int m_C;    
};

//语法：class 子类：继承方式 父类1 ，继承方式 父类2 
class Son : public Base1, public Base2 {
    public:
    Son() {
        cout << "Son constructor called" << endl;
        m_D = 50;
        m_B = 60; // duplicate member m_B from Base1, Base2 and Son
    }
    ~Son() {
        cout << "Son destructor called" << endl;
    }
    int m_D;
    int m_B;
};


int main() {
    Son s;
    //多继承容易产生成员同名的情况
    //通过使用类名作用域可以区分调用哪一个基类的成员
    
    cout << "m_A (from Base1): " << s.Base1::m_A << endl; // Accessing Base1 member // althrough Base1:: can be ignored, I recommend to use it
    cout << "m_B (from Son): " << s.m_B << endl;          // Accessing Son member, this will access the m_B from Son
    cout << "m_B (from Base1): " << s.Base1::m_B << endl; // Accessing Base1 member
    cout << "m_B (from Base2): " << s.Base2::m_B << endl; // Accessing Base2 member
    cout << "m_C (from Base2): " << s.Base2::m_C << endl; // Accessing Base2 member // althrough Base2:: can be ignored, I recommend to use it
    cout << "m_D: " << s.m_D << endl; // Accessing Son member

    return EXIT_SUCCESS;
}
