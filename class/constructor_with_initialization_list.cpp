#include <iostream>
using namespace std;
/*
4.2.6 初始化列表
作用：

C++提供了初始化列表语法，用来初始化属性

语法：构造函数()：属性1(值1),属性2（值2）... {}
*/
class Person { 
    public:
    ////传统方式初始化
	//Person(int a, int b, int c) {
	//	m_A = a;
	//	m_B = b;
	//	m_C = c;
	//}
    Person(int a, int b, int c) : m_A(a), m_B(b), m_C(c) {
        cout << "Person constructor called with initialization list." << endl;
    }
    ~Person() {
        cout << "Person destructor called." << endl;
    }
    void PrintPerson() {
		cout << "mA:" << m_A << endl;
		cout << "mB:" << m_B << endl;
		cout << "mC:" << m_C << endl;
	}

    private:
    int m_A;
    int m_B;
    int m_C;
};

int main(){
    Person person(10, 20, 30); // 使用初始化列表
    person.PrintPerson(); // 打印属性值
    return EXIT_SUCCESS;
}