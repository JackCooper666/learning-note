#include<iostream>
#include<string>
using namespace std;
class Animal {
public:
    Animal() {
        cout << "Animal constructor called." << endl;
    }
    //Speak函数就是虚函数
	//函数前面加上virtual关键字，变成虚函数，那么编译器在编译的时候就不能确定函数调用了。
    virtual void speak() {
        cout << "Animal speaks." << endl;
    }
    ~Animal() {
        cout << "Animal destructor called." << endl;
    }
};

class Dog : public Animal {
public:
    Dog() {
        cout << "Dog constructor called." << endl;
    }
    void speak() {
        cout << "Dog barks fuck ! fuck !" << endl;
    }
    ~Dog(){
        cout << "Dog destructor called." <<endl;
    }
};

//多态满足条件： 
//1、有继承关系
//2、子类重写父类中的虚函数
//多态使用：
//父类指针或引用指向子类对象

void dospeak(Animal &animal){
    animal.speak();
}

int main(){
    Dog d;
    dospeak(d);
    return 0;
}