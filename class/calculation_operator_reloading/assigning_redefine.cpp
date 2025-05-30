#include<iostream>
using namespace std;
class Person {
    public:
    Person(int age){
        m_age = new int(age);
    }
    int *m_age;
    ~Person() {
        if (m_age != nullptr) {
            delete m_age;
            m_age = nullptr; // Avoid dangling pointer
        }
    }

    Person& operator=(const Person &p) {
        cout << "Custom assignment operator called." << endl;
        if (this != &p) { // Check for self-assignment
            if (m_age != nullptr) {
                delete m_age; // Free existing memory
                m_age = nullptr; // Avoid dangling pointer
            }
            m_age = new int(*p.m_age); // Deep copy
        }
        return *this; // Return the current object to allow chained assignments
    }
};
int main() {
    Person p1(10);
    Person p2(20);
    Person p3(30);

    cout << "p1 age: " << *p1.m_age << endl; // Output: 10
    cout << "p2 age: " << *p2.m_age << endl; // Output: 20
    cout << "p3 age: " << *p3.m_age << endl; // Output: 30

    // p2 = p1; // This will call the default assignment operator // 浅拷贝
    p3 = p2 = p2 = p1;
    cout << "p1 age: " << *p1.m_age << endl; // Output: 10
    cout << "p2 age: " << *p2.m_age << endl; // Output: 10
    cout << "p3 age: " << *p3.m_age << endl; // Output: 10
    return EXIT_SUCCESS;
}