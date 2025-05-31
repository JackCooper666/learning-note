/*
the hpp file is diifferent from the h and cpp files
This file is a header file for class templated and their function members.

the h file is for normal class and functions

*/

#include <iostream>
#include <string>
using namespace std;

/*
class template inheritance
1. a normal class inherits from a class template
2. a class template inherits from a class template
*/

template <class Name2, class Age2, class Funding2>
class Father {
public:
    Father(Name2 name, Age2 age, Funding2 funding);

    // Father(Name2 name, Age2 age, Funding2 funding)
    //     : fa_name(name), fa_age(age), fa_funding(funding) {
    //     cout << "Father constructor called with name: " << fa_name
    //          << ", age: " << fa_age << ", funding: " << fa_funding << endl; 
    //     }
public:
    Name2 fa_name;
    Age2 fa_age;
    Funding2 fa_funding;
};
// write the function of class template outside the class
template <class Name2, class Age2, class Funding2>
Father<Name2, Age2, Funding2>::Father(Name2 name, Age2 age, Funding2 funding)
    : fa_name(name), fa_age(age), fa_funding(funding) {
    cout << "Father constructor called with name: " << fa_name
         << ", age: " << fa_age << ", funding: " << fa_funding << endl; 
}


// 1. a normal class inherits from a class template
class Son : public Father<string, int, double> {
public:
Son(string name, int age, double funding, string father_name = "Unknown", 
        int father_age = 0, 
        double father_funding = 0.0);
// Son(string name, int age, double funding, string father_name = "Unknown", 
//         int father_age = 0, 
//         double father_funding = 0.0)
//         : Father(father_name, father_age, father_funding), son_name(name), son_age(age), son_funding(funding){
//     cout << "Son constructor called with name: " << son_name
//          << ", age: " << son_age << ", funding: " << son_funding << endl;
// }
private:
    string son_name;
    int son_age;
    double son_funding;
};

Son::Son(string name, int age, double funding, string father_name, 
        int father_age, // the default value should be deleted in the function definition
        double father_funding)
        : Father(father_name, father_age, father_funding), son_name(name), son_age(age), son_funding(funding){
    cout << "Son constructor called with name: " << son_name
         << ", age: " << son_age << ", funding: " << son_funding << endl;
}



// 2. a class template inherits from a class template
template <class Name1, 
        class Age1, 
        class Funding1,
        class Name2,
        class Age2,
        class Funding2>
class Daughter : public Father<Name2, Age2, Funding2> {
    friend void fundingcalculate(Daughter<Name1, Age1, Funding1, Name2, Age2, Funding2> &d){
        cout << "Calculating funding for daughter: " << d.daughter_name << endl;
        // Example calculation
        d.daughter_funding += d.fa_funding; // Just an example, add 1000 to the funding
        cout << "Updated funding: " << d.daughter_funding << endl;
    }
public:
    Daughter(Name1 name, Age1 age, Funding1 funding, Name2 fa_name, Age2 fa_age, Funding2 fa_funding);
    // Daughter(Name1 name, Age1 age, Funding1 funding, Name2 fa_name, Age2 fa_age, Funding2 fa_funding)
    //     : daughter_name(name), daughter_age(age), daughter_funding(funding), Father<Name2, Age2, Funding2>(fa_name, fa_age, fa_funding) {
    //     cout << "Daughter constructor called with name: " << daughter_name
    //     << ", age: " << daughter_age << ", funding: " << daughter_funding << endl;
    // }

private:
    Name1 daughter_name;
    Age1 daughter_age;
    Funding1 daughter_funding;
};

template <class Name1, 
        class Age1, 
        class Funding1,
        class Name2,
        class Age2,
        class Funding2>
Daughter<Name1, Age1, Funding1, Name2, Age2, Funding2>::Daughter(Name1 name, Age1 age, Funding1 funding, Name2 fa_name, Age2 fa_age, Funding2 fa_funding)
        : daughter_name(name), daughter_age(age), daughter_funding(funding), Father<Name2, Age2, Funding2>(fa_name, fa_age, fa_funding) {
    cout << "Daughter constructor called with name: " << daughter_name
         << ", age: " << daughter_age << ", funding: " << daughter_funding << endl;
}