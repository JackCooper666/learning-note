#include <iostream>
using namespace std;

// 常函数：
// 成员函数后加const后我们称为这个函数为常函数
// 常函数内不可以修改成员属性
// 成员属性声明时加关键字mutable后，在常函数中依然可以修改

// 常对象：
// 声明对象前加const称该对象为常对象
// 常对象只能调用常函数

class Person {
    public:
    // 常函数
    void setAge(int age) const {
        //this->age = age; // This line will not compile because 'age' is a member variable and cannot be modified in a const member function
        id++; // This line can modify 'id' because it is mutable
    }
    void getAge() {
        cout << "Age: " << age << ", ID: " << id << endl;
    }
    private:
    int age = 0;
    mutable int id = 0; // mutable allows modification in const member functions
};

void test(){
    const Person person; // 常对象
    person.setAge(30); // This will compile because setAge is a const member function
    // person.getAge(); // This will print the age and id, but the function is not const function, so this line is wrong.
}

int main() {
    test();
    return EXIT_SUCCESS;
}