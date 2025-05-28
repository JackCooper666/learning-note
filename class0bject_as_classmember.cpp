#include<iostream>
using namespace std;
/*
4.2.7 类对象作为类成员
C++类中的成员可以是另一个类的对象，我们称该成员为 对象成员

例如：

class A {}
class B
{
    A a；
}
*/
class Phone{
    public:
    Phone(string pphonename) : phonename(pphonename) {
        cout << "Phone constructor called for " << phonename << endl;
    }
    ~Phone() {
        cout << "Phone destructor called for " << phonename << endl;
    }
    string phonename;
};
class Person {
    public:
    Person(string per_id, string name) : id(per_id), phone(name) {
        cout << "Person constructor called for " << id << endl;
    }
    ~Person() {
        cout << "Person destructor called for " << id << endl;
    }
    string id;
    Phone phone;
};

int main() {
    Person person("zewen", "iPhone14");
    cout << "Person ID: " << person.id << ", Phone Name: " << person.phone.phonename << endl;
    return 0;
}