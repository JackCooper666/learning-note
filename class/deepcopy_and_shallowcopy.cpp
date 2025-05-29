#include<iostream>
using namespace std;

// 总结：如果属性有在堆区开辟的，一定要自己提供拷贝构造函数
// ，防止浅拷贝带来的同一堆区重复释放bug
// 如果属性没有在堆区开辟的，c++提供的默认拷贝构造函数就可以了
// 默认拷贝构造函数是浅拷贝

class Person {
    public:
    Person(int age, int height_value) { 
        age_person = age;
        height = new int(height_value); // 在堆区开辟内存
        cout << "Person constructor called." << endl;
    }
    Person(const Person &p) {
        cout << "Person copy constructor called." << endl;
        age_person = p.age_person;
        height = new int(*p.height); // 深拷贝
        // height = p.height// 浅拷贝
    }
    ~Person() {
        if (height != nullptr) {
            delete height; // 释放堆区内存
            height = nullptr; // 防止悬空指针
        } else
        {
            cout << "Height pointer is already null." << endl;
        }
        
        cout << "Person destructor called." << endl;
    }
    int age_person;
    int *height;
};

int main(){
    Person person1(25, 180); // 调用有参构造函数
    Person person2(person1); // 调用拷贝构造函数，进行深拷贝
    return EXIT_SUCCESS;
}