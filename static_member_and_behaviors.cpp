#include <iostream>
using namespace std;
// 4.2.8 静态成员
// 静态成员就是在成员变量和成员函数前加上关键字static，称为静态成员

// 静态成员分为：

// 静态成员变量
// 所有对象共享同一份数据
// 在编译阶段分配内存
// 类内声明，类外初始化

// 静态成员函数
// 所有对象共享同一个函数
// 静态成员函数只能访问静态成员变量, cannot access非静态成员变量

class Person {
    public:
    // 静态成员变量
    // 类内声明
    static int count; // 静态成员变量
    static void modifier(){
        cout << "Modifier called" << endl;
        id++; // 修改静态成员变量
        cout << "New id: " << id << endl;
    }
    static void printid() {
        cout << "Current id: " << id << endl;
    }
    static int getId(int newId) {
        cout << "getId called with newId: " << newId << endl;
        return id = newId; // 修改静态成员变量
    }
    void pppprint() {
        print(); // 调用静态成员函数
    }
    private: 
    // 静态成员函数
    // 类内声明
    // prviate static member function has the access limitation as well, it needs a public member function to access it
    static void print() {
        cout << "This is a static member function." << endl;
    }
    static int id; // 静态成员变量
};
// 静态成员变量
// 类外初始化
int Person::count = 0; // 静态成员变量初始化
int Person::id = 0; // 静态成员变量初始化


void test01() {
    Person p1;
    Person p2;

    //静态成员变量两种访问方式
    p1.count = 10; // 通过对象访问静态成员变量
    
    //1、通过对象
    cout << "Person 1 count: " << p1.count << endl; // 通过类名访问静态成员变量
    cout << "Person 2 count: " << p2.count << endl; // 通过类名访问静态成员变量
    // 2、通过类名
    Person::count = 30; // 通过类名访问静态成员变量
    cout << "Person 1 count: " << p1.count << endl; // 通过类名访问静态成员变量
    cout << "Person 2 count: " << p2.count << endl; // 通过类名访问静态成员变量
    cout << "Person count: " << Person::count << endl; // 通过类名访问静态成员变量

    // the private static member variable cannot be accessed directly outside the class
    // p2.id = 20; // 通过对象访问静态成员变量
    // //1、通过对象
    // cout << "Person 1 id: " << p1.id << endl; // 通过类名访问静态成员变量
    // cout << "Person 2 id: " << p2.id << endl; // 通过类名访问静态成员变量
}

void test02() {
    // 静态成员函数
    // 通过类名访问静态成员函数
    Person::printid(); // 通过类名访问静态成员函数
    Person::getId(30); // 通过类名访问静态成员函数
    Person::modifier(); // 通过类名访问静态成员函数
    // 通过对象访问静态成员函数
    Person p1;
    Person p2;
    p1.printid(); // 通过对象访问静态成员函数
    p2.getId(50); // 通过对象访问静态成员函数
    p1.modifier(); // 通过对象访问静态成员函数
    p2.printid(); // 通过对象访问静态成员函数
    
    p1.pppprint(); // 通过对象访问静态成员函数
}   

int main() {
    // test01();
    test02();
    return EXIT_SUCCESS;
}