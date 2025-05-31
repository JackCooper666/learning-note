#include <iostream>
#include <string>
using namespace std;


class Animal {
public:
    Animal() {
        cout << "Animal constructor called." << endl;
    }
    int age;
};

//继承前加virtual关键字后，变为虚继承
//此时公共的父类Animal称为虚基类
class Sheep : virtual public Animal {
public:
    Sheep() {
        cout << "Sheep constructor called." << endl;
    }
    string woolColor;
};
class Camel : virtual public Animal {
public:
    Camel() {
        cout << "Camel constructor called." << endl;
    }
    string humpSize;
};
class alpaca : public Sheep, public Camel {
public:
    alpaca() {
        cout << "alpaca constructor called." << endl;
    }
    string fleeceType;
};

int main() {
    alpaca myAlpaca;
    /*
    the sheep and camel classes both inherit from the Animal class, so both have the age member.
    when the alpace class access the age member directly "myAplaca,age = 5", the compiler does not know which age member to use,
    so it will report an error.
    To resolve this ambiguity, we can use the scope resolution operator to specify which base class's member we want to access.
    
    myAplace.Sheep::age = 10; // Accessing the age from the Sheep class
    myAplace.Camel::age = 10; // Accessing the age from the Camel class

    However, since both Sheep and Camel inherit from Animal, and we only want to use the Animal's member in the alpaca class directly.
    the virtual inheritance ensures that there is only one instance of the Animal class in the alpaca class,
    so we can access the age member directly without ambiguity.
    the virtual inheritance is this:
    class Camel : virtual public Animal
    class Sheep : virtual public Animal

    Therefore, we can access the age member directly in the alpaca class without specifying the base class.

    In addition, the myAlpaca.Sheep::age, myAlpaca.Camel::age, and myAlpaca.age in the alpaca class are all the same member
    , they are pointing to the same memory address.
    Therefore, if we change one of them, the others will also change.
    */
    myAlpaca.age = 5; // Accessing the age from the Animal class
    myAlpaca.Sheep::woolColor = "White"; // Accessing the woolColor from the Sheep class
    myAlpaca.Camel::humpSize = "Small"; // Accessing the humpSize from the Camel class
    myAlpaca.fleeceType = "Soft"; // Accessing the fleeceType from the alpaca class

    cout << "Age: " << myAlpaca.age << endl;
    cout << "Wool Color: " << myAlpaca.Sheep::woolColor << endl;
    cout << "Hump Size: " << myAlpaca.Camel::humpSize << endl;
    cout << "Fleece Type: " << myAlpaca.fleeceType << endl;

    myAlpaca.Sheep::age = 10; // Accessing the age from the Sheep class
    myAlpaca.Camel::age = 20; // Accessing the age from the Camel class
    cout << "After changing age in Sheep and Camel:" << endl;
    cout << "Age: " << myAlpaca.age << endl; // Accessing the age from the Animal class



    return 0;
}