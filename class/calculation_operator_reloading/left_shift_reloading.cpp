#include <iostream>
using namespace std;

/*
left shift operator is "<<"
*/

class Person {
    friend ostream& operator<<(ostream& cout, const Person& p);
    public:
    Person(int a, int b) {
        m_A = a;
        m_B = b;
    }
    private:
    int m_A;
    int m_B;

    // the left shift operator cannot be redifened 
    // as a member function
    // as the only p.operator<<(cout) will be the p << cout, rather than the cout << p.
};

ostream& operator<<(ostream& cout, const Person& p){
    cout << "m_A: " << p.m_A << ", m_B: " << p.m_B;
    return cout; // return the cout object to allow chaining
}

void test01() {
    Person p1(10, 20);
    cout << p1 << endl; // Calls the non-member operator<<
}
int main() {
    test01();
    return EXIT_SUCCESS;
}