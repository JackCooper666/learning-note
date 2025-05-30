#include<iostream>
using namespace std;
class Person {
    public:
    Person(string name,int age){
        m_name = name;
        m_age = age;
    }
    string m_name;
    int m_age;
    // 重载关系运算符
    bool operator>=(const Person &p) const {
        // cout << "Custom >= operator called." << endl;
        return this->m_age >= p.m_age; // 比较年龄
    }
};
int main(){
    Person p1("Alice", 30);
    Person p2("Bob", 25);
    Person p3("Charlie", 30);

    cout << "p1 >= p2: " << (p1 >= p2) << endl; // Output: 1 (true)
    cout << "p1 >= p3: " << (p1 >= p3) << endl; // Output: 1 (true)
    cout << "p2 >= p3: " << (p2 >= p3) << endl; // Output: 0 (false)

    return EXIT_SUCCESS;
}