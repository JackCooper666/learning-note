#include <iostream>
#include <string>
using namespace std;

// 多态使用时，如果子类中有属性开辟到堆区，那么父类指针在释放时无法调用到子类的析构代码
// add virtual destructor or pure virtual deconstructor to the base class to ensure proper cleanup
// if an class has virtual deconstructor, it will be an abstract class

class Animal {
    public:
    virtual void sound() {
        cout << "Animal makes a sound" << endl;
    }
    // virtual deconstructor ensures that the derived class destructor is called
    virtual ~Animal() {
        cout << "Animal destructor called" << endl;
    }

    // virtual ~Animal() = 0; // pure virtual destructor ensures that the derived class destructor is called
};
// Animal::~Animal() {
//     // pure virtual destructor must be defined
//     cout << "Animal destructor called" << endl;
// }
class Dog : public Animal {
    public:
    Dog(string name){
        this->name = new string(name);
        cout << "Dog constructor called" << endl;
    }
    virtual void sound(){
        cout << *name << " barks" << endl;
    }
    string *name;
    ~Dog() {
        cout << "Dog destructor called" << endl;
        if (name) {
            delete name; // free the memory allocated for name
            name = nullptr; // set pointer to nullptr to avoid dangling pointer
        }
    }
};

int main () {
    Animal *animal = new Dog("Buddy");
    animal->sound();
    delete animal; // this will call Dog destructor and then Animal destructor
    return 0;
}