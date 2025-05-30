#include<iostream>
using namespace std;
/*
1. public inherit
2. protected inherit
3. private inherit
*/

// father class
class father {
    public:
    // constructor
    // father(int a = 0, int b = 0, int c = 0) : b_a(a), b_b(b), b_c(c) {
    //     cout << "father constructor called" << endl;
    // }
    int b_a;

    protected:
    int b_b;

    // the private members cannot be inherited 
    // no metter which inherit methods
    private:
    int b_c;
};

// child class 1 
// public inherit:
// the public members in the father class 
// will be public in the child class
// the protected members in the father class 
// will be protected in the child class
class Child1 : public father {
    public:
    Child1(int a = 0, int b = 0){
        b_a = a; // public member
        b_b = b; // protected member
        // b_c = 0; // error: 'b_c' is private within this context
    }
};

void test_public_inherit() {
    // father b(1,2,3);
    // cout << "Base b_a: " << b.b_a << endl; // accessible
    Child1 c1(10,20);
    cout << "Child1 b_a: " << c1.b_a << endl; // accessible
    /*
    child inherits father class members
    , but the inherited members in the father and child are separated
    , so the inherited members in the child class and the father class
    are not the same members and can have different values

    However, inherited functions are the same
    */
}


// child class 2
// protected inherit:
// all the public and protected members in the father class
// will be protected in the child class
class Child2 : protected father {
    public:
    Child2(int a = 0, int b = 0){
        b_a = a; // public member
        b_b = b; // protected member
        // b_c = 0; // error: 'b_c' is private within this context
    }

    void show() {
        cout << "Child2 b_a: " << b_a << endl; // accessible within the class
        cout << "Child2 b_b: " << b_b << endl; // accessible within the class
        // cout << "Child2 b_c: " << b_c << endl; // error: 'b_c' is private within this context
    }
};
void test_protected_inherit() {
    // father b(1,2,3);
    // cout << "Base b_a: " << b.b_a << endl; // error: 'b_a' is inaccessible
    Child2 c2(10,20);
    // cout << "Child2 b_a: " << c2.b_a << endl; // error: 'b_a' is inaccessible
    c2.show(); // accessible through a public method

}



// child class 3
// private inherit:
// all the public and protected members in the father class
// will be private in the child class
class Child3 : private father {
    public:
    Child3(int a = 0, int b = 0){
        b_a = a; // public member in father, now private in Child3
        b_b = b; // protected member in father, now private in Child3
        // b_c = 0; // error: 'b_c' is private within this context
    }

    void show() {
        cout << "Child3 b_a: " << b_a << endl; // accessible within the class
        cout << "Child3 b_b: " << b_b << endl; // accessible within the class
        // cout << "Child3 b_c: " << b_c << endl; // error: 'b_c' is private within this context
    }
};
void test_private_inherit() {
    // father b(1,2,3);
    // cout << "Base b_a: " << b.b_a << endl; // error: 'b_a' is inaccessible
    Child3 c3(10,20);
    /*
    the code is correct without the decalaration and initialization of father b,
    the Child3 c3(10,20) will call the father constructor firstly, then the Child3 constructor

    then the CIld3 destructor will be called firstly, then the father destructor will be called
    */


    // cout << "Child3 b_a: " << c3.b_a << endl; // error: 'b_a' is inaccessible
    c3.show(); // accessible through a public method
}

int main() {
    // test_public_inherit();
    // test_protected_inherit();
    test_private_inherit();
    return 0;
}