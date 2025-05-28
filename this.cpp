#include <iostream>
using namespace std;

class Person {
    public:
    //1、当形参和成员变量同名时，可用this指针来区分
    void setAge(int age) {
        age = age; // This line has a bug
        this->age = age; // Corrected line to use 'this' pointer
    }
    void getAge() const {
        cout << "Age: " << age << endl;
    }

    // 在类的非静态成员函数中返回对象本身，可使用return *this
    Person& addage(Person person){
        this->age += person.age; // Correctly adds the age of the passed person
        return *this; // Returns the current object
    }
    /*
    please note that you cannot use the "Person addage(P0erson person)"
    which will create a new object and return it, but not the current object.
    This is because the return type is not a reference, but a value.
    If you want to return the current object, you should use "Person& addage(Person person)" 
    
    */
    private:
    int age;
};
void test01() {
    Person person;
    person.setAge(30);
    person.getAge(); // This will not print the expected age due to the bug in setAge method.
    // The age is not set correctly due to the bug in setAge method.
    // This will not print the expected age.
    cout << "Person's age is set." << endl;
}
void test02(){
    Person Person1;
    Person1.setAge(30);
    Person Person2;
    Person2.setAge(20);
    Person1.addage(Person2).addage(Person2).getAge(); // This will print the age after adding Person2's age twice

}
int main() {
    // test01();
    test02();
    return 0;
}