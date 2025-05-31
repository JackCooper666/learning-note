#include <iostream>
#include <string>
using namespace std;
/*
Function Template Declaration followed with the definition of the function.

please note that:
1. typename means this is a template function not the template class.
2. 模板必须要确定出T的数据类型，才可以使用
3. the data type of the input variable for the template function should be the same as the T
*/
template <typename T>
T add(T a, T b) {
    return a + b;
}


void test01(){
    int a = 2;
    int b = 3;
    double x = 2.5;
    double y = 3.5;
    // Using the template function with integers
    int intResult = add<int>(a, b);
    cout << "Integer addition result: " << intResult << endl;
    // Using the template function with doubles
    double doubleResult = add<double>(x, y);
    cout << "Double addition result: " << doubleResult << endl;
}


/*
普通函数与函数模板区别：
普通函数调用时可以发生自动类型转换（隐式类型转换）
函数模板调用时，如果利用自动类型推导，不会发生隐式类型转换 // do not recommend using this way
如果利用显示指定类型的方式，可以发生隐式类型转换

普通函数与函数模板的调用规则
调用规则如下：
如果函数模板和普通函数都可以实现，优先调用普通函数
可以通过显示指定类型的方式来强制调用函数模板
函数模板也可以发生重载
如果函数模板可以产生更好的匹配,优先调用函数模板


模板的局限性:
如果T的数据类型传入的是像Person这样的自定义数据类型，也无法正常运行
因此C++为了解决这种问题，提供模板的重载，可以为这些特定的类型提供具体化的模板
*/

class Person
{
public:
	Person(string name, int age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}
	string m_Name;
	int m_Age;
};


int myadd02(int a, int b) {
    cout << "Calling normal function myadd02(int, int)" << endl;
    return a + b;
}

template <typename T>
T myadd02(T a, T b) {
    cout << "Calling template function myadd02<T>(T, T)" << endl;
    return a + b;
}

template <typename T>
T myadd02(T a, T b, T c){
    cout << "Calling template function myadd02<T>(T, T, T)" << endl;
    return a + b + c;
}
// Correct specialization for Person (matches the two-argument template)
template<> 
Person myadd02(Person a, Person b) {
    cout << "Calling specialized template function myadd02<Person>(Person, Person)" << endl;
    return Person(a.m_Name + " & " + b.m_Name, a.m_Age + b.m_Age);
}
// wrong specialization example
// the & in the parameter type is not correct, it should be a value type
// as the prrevious template function is using value type

// template<> 
// Person myadd02<Person>(Person &a, Person &b) {
//     cout << "Calling specialized template function myadd02<Person>(Person, Person)" << endl;
//     return Person(a.m_Name + " & " + b.m_Name, a.m_Age + b.m_Age); // Assuming we want to combine names and add ages
// }

// wrong specialization example
/*
Return Type Mismatch
The original template returns T, but your specialization hardcodes int.
This is inconsistent because myadd02<Person> should logically return a Person (but you're returning an int).
*/
// template<> int myadd02(Person &a, Person &b) {
//     cout << "Calling specialized template function myadd02<Person>(Person, Person)" << endl;
//     return a.m_Age + b.m_Age; // Assuming we want to add ages of two Person objects
// }



void test02() {
    int c = 10;
    char d = 'B';
    int e = 20;
    cout << "myadd02(c, d): " << myadd02(c, d) << endl; // Calls the normal function    
    cout << "myadd02<int>(c, d): " << myadd02<int>(c, d) << endl; // Calls the template function with explicit type
    cout << "myadd02(c,d,e): " << myadd02<int>(c, d, e) << endl; // Calls the template function with three parameters
    // Test Person objects
    Person p1("Alice", 20);
    Person p2("Bob", 30);
    Person result = myadd02<Person>(p1, p2);
    cout << "Combined person: " << result.m_Name << ", age " << result.m_Age << endl;
}


int main () {
    // cout << "------------------------" << endl;
    // test01();
    cout << "------------------------" << endl;
    test02();
    return 0;
}