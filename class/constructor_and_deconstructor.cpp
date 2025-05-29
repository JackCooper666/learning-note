#include <iostream>
using namespace std;

/*
构造函数语法：类名(){}

构造函数，没有返回值也不写void
函数名称与类名相同
构造函数可以有参数，因此可以发生重载
程序在调用对象时候会自动调用构造，无须手动调用,而且只会调用一次
*/

/*
析构函数语法： ~类名(){}

析构函数，没有返回值也不写void
函数名称与类名相同,在名称前加上符号 ~
析构函数不可以有参数，因此不可以发生重载
程序在对象销毁前会自动调用析构，无须手动调用,而且只会调用一次
*/

/*
默认情况下，c++编译器至少给一个类添加3个函数

1．默认构造函数(无参，函数体为空)

2．默认析构函数(无参，函数体为空)

3．默认拷贝构造函数，对属性进行值拷贝

构造函数调用规则如下：

如果用户定义有参构造函数，c++不在提供默认无参构造，但是会提供默认拷贝构造

如果用户定义拷贝构造函数，c++不会再提供其他构造函数
*/

class Person { 
    public:
        // 无参（默认）构造函数
        Person() {
            cout << "Person constructor called." << endl;
        }

        // 带参构造函数
        Person(int age) {
            age_person = age;
            cout << "Person constructor with age called: " << age << endl;
        }

        //拷贝构造函数
        Person(const Person &p) {
            age_person = p.age_person;
            cout << "Person copy constructor called." << endl;
        }

        // 析构函数
        ~Person() {
            cout << "Person destructor called." << endl;
        }
    private:
        int age_person = 0;
};

void test01() {
    Person person1; // call the noparam (default) constructor
    
    // 括号法，常用
    Person person2(25); // call the parameterized constructor
    Person person3(person2); // call the copy constructor

    // 显式法
    Person person4 = Person(30); // call the parameterized constructor
    Person person5 = Person(person4); // call the copy constructor

    // 隐式转换法
    Person person6 = 35; // call the parameterized constructor
    Person person7 = person6; // call the copy constructor
}

//拷贝构造函数
        /*
        C++中拷贝构造函数调用时机通常有三种情况
        1. 使用一个已经创建完毕的对象来初始化一个新对象
        2. 值传递的方式给函数参数传值
        3. 以值方式返回局部对象
        */
void dowork01(Person p) {
    cout << "Doing work with person." << endl;
}
// void dowork01(Person &p) {
//     cout << "Doing work with person by reference." << endl;
// }
/*
the Person &p will create a reference for the input class, 
and if I do some changes in the function, 
the original class will be modified as well.

The Person p is to create a local class in the function 
which will not affect the original class
*/

Person dowork02() {
    Person p(40);
    cout << "Doing work with person by value." << endl;
    return p; // 以值方式返回局部对象
}
void test02() {
    // 1. 使用一个已经创建完毕的对象来初始化一个新对象
    Person person1(20);
    Person person2(person1); // 调用拷贝构造函数
    Person person3 = person1; // 也会调用拷贝构造函数
    // 2. 值传递的方式给函数参数传值
    dowork01(person1); // 调用拷贝构造函数
    // 3. 以值方式返回局部对象
    Person person4 = dowork02();
	cout << (int *)&person4 << endl;

}


int main(){
    // test01();
    // test02();

    return EXIT_SUCCESS;
}
