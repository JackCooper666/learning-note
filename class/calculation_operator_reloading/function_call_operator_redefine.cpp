#include <iostream>
#include <string>
using namespace std;

class MyPrint
{
private:
    string prefix;  // New member variable
public:
    // Constructor
    MyPrint(const string& pre = "") : prefix(pre) {}
    
    void operator()(string text) const
    {
        cout << prefix << text << endl;
    }
};

void test01()
{
    // Using default constructor
    MyPrint myFunc1;
    myFunc1("hello world");  // Output: "hello world"
    
    // Using constructor with parameter
    MyPrint myFunc2("Message: ");
    myFunc2("hello world");  // Output: "Message: hello world"
}

class MyAdd
{
private:
    int baseValue;  // New member variable
public:
    // Constructor
    MyAdd(int base = 0) : baseValue(base) {}
    
    int operator()(int v1, int v2) const
    {
        return baseValue + v1 + v2;
    }
};

void test02()
{
    // Using default constructor
    MyAdd add1;
    int ret1 = add1(10, 10);
    cout << "ret1 = " << ret1 << endl;  // Output: 20
    
    // Using constructor with parameter
    MyAdd add2(5);
    int ret2 = add2(10, 10);
    cout << "ret2 = " << ret2 << endl;  // Output: 25
    
    // Anonymous object with constructor
    cout << "MyAdd(100)(100,100) = " << MyAdd(100)(100, 100) << endl;  // Output: 300
}

int main() {
    test01();
    test02();
    return 0;
}