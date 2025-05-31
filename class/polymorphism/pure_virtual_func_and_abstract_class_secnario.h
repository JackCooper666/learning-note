#include <iostream>
#include <string>
using namespace std;

class Abstractdrink {
    public:
    //纯虚函数
	//类中只要有一个纯虚函数就称为抽象类
	//抽象类无法实例化对象
	//子类必须重写父类中的纯虚函数，否则也属于抽象类
    virtual void boil() = 0;
    virtual void pour() = 0;
    virtual void package() = 0;
    virtual void season() = 0;
    void make() {
        boil();
        pour();
        package();
        season();
    }
};

class Tea : public Abstractdrink {
    public:
    virtual void boil() {
        cout << "Boiling water for tea." << endl;
    }
    virtual void pour() {
        cout << "Pouring tea into cup." << endl;
    }
    virtual void package() {
        cout << "Packaging tea." << endl;
    }
    virtual void season() {
        cout << "Adding lemon to tea." << endl;
    }
};
class Coffee : public Abstractdrink {
    public:
    virtual void boil() {
        cout << "Boiling water for coffee." << endl;
    }
    virtual void pour() {
        cout << "Pouring coffee into cup." << endl;
    }
    virtual void package() {
        cout << "Packaging coffee." << endl;
    }
    virtual void season() {
        cout << "Adding sugar to coffee." << endl;
    }
};