#include <iostream>
using namespace std;
class father {
    public:
    father(int a = 0, int b = 0, int c = 0) : m_a(a), m_b(b), m_c(c) {
        cout << "father constructor called" << endl;
    }
    int m_a;
    int m_b;

    void func() {
        cout << "father func called" << endl;
    }

    //当子类与父类拥有同名的成员函数，子类会隐藏父类中所有版本的同名成员函数
	//如果想访问父类中被隐藏的同名成员函数，需要加父类的作用域
    void func(int a){
        cout << "father func with int called: " << a << endl;
    }

    protected:

    private:
    int m_c;
};

class Child1 : public father {
    public:
    Child1(int a = 5, int b = 5){
        m_a = a; // public member
        m_b = b; // protected member
        // m_c = 0; // error: 'm_c' is private within this context
    }
    int m_a;
    void func() {
        cout << "Child1 func called" << endl;
    }
};
void test_public_inherit() {
    Child1 c1(10, 20); // this will call the father constructor to create a new father object first
    cout << "Child1 m_a: " << c1.m_a << endl; // accessible
    cout << "Child1 m_b: " << c1.m_b << endl; // accessible
    cout << "Child1 inherited m_a: " << c1.father::m_a << endl; // accessible // these line will output 0, the initialization value from father constructor
    // this is because m_a in Child1 is a different member than m_a in father
    // the Child1 constructor initializes its own m_a, not the inherited one
    // the priority of the member in Child1 is higher than the inherited one

    cout << "Child1 inherited m_b: " << c1.father::m_b << endl; // accessible
    c1.father::m_a = 30; // modifying the inherited member
    cout << "Child1 modified inherited m_a: " << c1.father::m_a << endl; // accessible
    c1.m_a = 50;
    cout << "Child1 modified inherited m_a: " << c1.father::m_a << endl; // accessible

    c1.func(); // calls Child1's func
    c1.father::func(); // calls father's func
    c1.father::func(100); // calls father's func with int parameter

}

int main(){
    test_public_inherit();
    return 0;
}
