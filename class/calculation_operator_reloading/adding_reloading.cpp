#include<iostream>
using namespace std;
class Person {
    public:
    Person(int a, int b){
        m_A = a;
        m_B = b;
    }
    Person operator+(const Person& other) const {
        return Person(m_A + other.m_A, m_B + other.m_B);
    }
    int m_A;
    int m_B;
};

Person operator+(const Person& p1, const Person& p2) {
    return Person(p1.m_A + p2.m_A, p1.m_B + p2.m_B);
}

Person operator+(const Person& p1, int num) {
    return Person(p1.m_A + num, p1.m_B + num);
}

void test01() {
    Person p1(10, 20);
    Person p2(30, 40);
    Person p3 = p1 + p2; // Calls the member operator+
    cout << "p3.m_A: " << p3.m_A << ", p3.m_B: " << p3.m_B << endl;
    Person p4 = p1 + 100; // Calls the non-member operator+
    cout << "p4.m_A: " << p4.m_A << ", p4.m_B: " << p4.m_B << endl;

    // Person p4 = operator+(p1, p2); // Calls the non-member operator+
    // cout << "p4.m_A: " << p4.m_A << ", p4.m_B: " << p4.m_B << endl;
}
int main(){
    test01();
    return EXIT_SUCCESS;
}