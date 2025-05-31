#include <iostream>
#include <string>
using namespace std;

/*
the class template declaration
This is a class template declaration for a class named Person1.
It uses two template parameters: NameType and AgeType declared with class keyword.

类模板与函数模板区别主要有两点：

类模板没有自动类型推导的使用方式
类模板在模板参数列表中可以有默认参数

类模板中成员函数创建时机
类模板中成员函数和普通类中成员函数创建时机是有区别的：

普通类中的成员函数一开始就可以创建
类模板中的成员函数在调用时才创建
*/
template <class NameType = string, class AgeType = int>
            // NameType is set to string by default
            // the AgeType is set to int by default
class Person {
    public:
        Person(NameType name, AgeType age, int id = 0) {
            this->m_Name = name;
            this->m_Age = age;
            this->m_Id = id;
        }
        void display() const {
            cout << "Name: " << m_Name << ", Age: " << m_Age << endl;
            cout << "ID: " << m_Id << endl;
        }
    public:
        NameType m_Name;
        AgeType m_Age;
        int m_Id;        
};

void test01() {
    // Create a Person object with string and int types
    Person<string, int> person1("Alice", 30, 2002);
    person1.display();

}
/*
类模板对象做函数参数
学习目标：

类模板实例化出的对象，向函数传参的方式:
指定传入的类型 --- 直接显示对象的数据类型

*/

void writeage2id(Person<string, int> &p) {
    p.m_Id = p.m_Age;
    cout << "Updated ID based on age: " << p.m_Id << endl;  
}

void test02() {
    Person<string, int> person2("Bob", 25);
    person2.display();
    writeage2id(person2); // Pass the object to the function
    person2.display(); // Display the updated object
}
int main () {
    // test01();
    // test02();
    return 0;
}