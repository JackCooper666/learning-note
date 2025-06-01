/*
案例描述: 实现一个通用的数组类，要求如下：

可以对内置数据类型以及自定义数据类型的数据进行存储
将数组中的数据存储到堆区
构造函数中可以传入数组的容量
提供对应的拷贝构造函数以及operator=防止浅拷贝问题
提供尾插法和尾删法对数组中的数据进行增加和删除
可以通过下标的方式访问数组中的元素
可以获取数组中当前元素个数和数组的容量
*/
#include <iostream>
#include <string>
using namespace std;
#include "array_template.hpp"

class Person {
public:
    Person(){} // 默认构造函数
    /*
    why we need this constructor?
    MyArrary<Person> personArray(3); create the memory space by the "new" with capacity 3, 
    and the Person class needs a constructor to initialize the objects during the creating.
    if the Person(string name, int age) : name(name), age(age) {} was defined, 
    the compile will not create a default no variable contstructor automatically,
    */
    Person(string name, int age) : name(name), age(age) {}
    int age;
    string name;
};
ostream& operator<<(ostream& os, const Person& p) {
    os << "Name: " << p.name << ", Age: " << p.age;
    return os;
}
int main() {
    // 测试内置数据类型
    MyArrary<int> intArray(5);
    intArray.push_back(1);
    intArray.push_back(2);
    intArray.push_back(3);
    intArray.printsize();
    intArray.printcapacity();
    cout << "Element at index 1: " << intArray[1] << endl;
    intArray.pop_back();
    intArray.printsize();

    // 测试自定义数据类型
    MyArrary<Person> personArray(3);
    personArray.push_back(Person("Alice", 30));
    personArray.push_back(Person("Bob", 25));
    personArray.printsize();
    personArray.printcapacity();
    cout << "Element at index 0: " << personArray[0] << endl;
    personArray.pop_back();
    personArray.printsize();
    personArray.push_back(Person("Charlie", 28));
    cout << "Element at index 1: " << personArray[1] << endl;
    
    // 测试拷贝构造函数
    cout << "Testing copy constructor:" << endl;
    MyArrary<Person> copiedArray(personArray); // 调用拷贝构造函数
    copiedArray.printsize();
    copiedArray.printcapacity();
    cout << "Element at index 0 in copied array: " << copiedArray[0] << endl;
    copiedArray.push_back(Person("David", 22));
    cout << "Element at index 2 in copied array: " << copiedArray[2] << endl;
    copiedArray.printsize();
    copiedArray.printcapacity();    

    // 测试赋值操作符
    cout << "Testing assignment operator:" << endl;
    personArray = copiedArray; // 调用赋值操作符
    personArray.printsize();
    personArray.printcapacity();
    cout << "Element at index 0 in original array after assignment: " << personArray[0] << endl;
    personArray.push_back(Person("Eve", 35));
    cout << "Element at index 2 in original array after assignment: " << personArray[2] << endl;
    return 0;
}