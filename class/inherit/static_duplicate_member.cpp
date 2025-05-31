#include <iostream>
using namespace std;
class Base {
public:
    static int value;
    static void func() {
        cout << "Base::func() called, value = " << value << endl;
    }
    static int func(int a) {
        value = a;
        cout << "Base::func(int) called, value = " << value << ", a = " << a << endl;
    }
};
int Base::value = 42;

class Derived : public Base {
public:
    //同名成员属性
    static int value; // This will cause a static member name conflict with Base

    //同名成员函数
    static void func() {
        cout << "Derived::func() called, value = " << value << endl;
    }
};
int Derived::value = 84; // This will cause a static member name conflict with Base

int main() {
    //同名成员属性
    //通过对象访问
    Derived d;
    cout << "通过对象访问： " << endl;
    cout << "Son  下 value = " << d.value << endl;
	cout << "Base 下 value = " << d.Base::value << endl;
    //通过类名访问
    cout << "通过类名访问： " << endl;
    cout << "Son::value = " << Derived::value << endl;
    cout << "Base::value = " << Derived::Base::value << endl;
    
    //同名成员函数
    //通过对象访问
    cout << "通过对象访问： " << endl;
    d.func(); // Calls Derived::func()
    d.Base::func(); // Calls Base::func()
    d.Base::func(100); // Calls Base::func(int) 

    //通过类名访问
    cout << "通过类名访问： " << endl;
    Derived::Base::func(); // Calls Base::func()
    Derived::Base::func(200); // Calls Base::func(int)
    Derived::func(); // Calls Derived::func()

}