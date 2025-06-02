#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // it includes the algorithms for STL, such as for_each, sort, etc.
using namespace std;
class Person {
public:
    string name;
    int age;

    Person(string n, int a) : name(n), age(a) {}
};

void printint_for_each(int value) {
    cout << value << " ";
}

void printint(vector<int> &vec) {
    for (vector<int>::iterator it = vec.begin(); it != vec.end(); it++) {
        cout << *it << " ";
    }
}

// basic usage of vector
void test01(){
    vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);

    // Print the vector elements
    // 1. while loop
    //每一个容器都有自己的迭代器，迭代器是用来遍历容器中的元素
    // 迭代器是一个指针，指向容器中的元素
	//v.begin()返回迭代器，这个迭代器指向容器中第一个数据
	//v.end()返回迭代器，这个迭代器指向容器元素的最后一个元素的下一个位置
	//vector<int>::iterator 拿到vector<int>这种容器的迭代器类型
    vector<int>::iterator it = vec.begin();
    cout << "Using while loop: " << endl;
    while (it != vec.end()) {
        cout << *it << " ";
        it++;

    }
    cout << endl;
    // 2. for loop
    cout << "Using for loop: " << endl;
    printint(vec);
    cout << endl;
    // 3. STL algorithm: for_each
    cout << "Using for_each: " << endl;
    for_each(vec.begin(), vec.end(), printint_for_each);
    cout << endl;
}

// vector template with self defined variable type or the pointer to class
void test02() {
    cout << "Using vector with self defined variable type: " << endl;
    vector<Person> vp;
    Person p1("Alice", 30);
    Person p2("Bob", 25);
    Person p3("Charlie", 35);
    vp.push_back(p1);
    vp.push_back(p2);
    vp.push_back(p3);
    for (vector<Person>::iterator it = vp.begin(); it != vp.end(); it++) {
        cout << "Name: " << (*it).name << ", Age: " << (*it).age << endl;
        cout << "Name: " << it->name << ", Age: " << it->age << endl;
    }

    // vector of pointers to class
    cout << "Using vector of pointers to class: " << endl;
    vector<Person*> vpp;
    Person pp1("Alice", 30);
    Person pp2("Bob", 25);
    Person pp3("Charlie", 35);
    vpp.push_back(&pp1);
    vpp.push_back(&pp2);
    vpp.push_back(&pp3);

    /*
    these lines are wrong
    // vpp.push_back(&Person("David", 28));
    // vpp.push_back(&Person("Eve", 22));
    Person("David", 28) creates a temporary Person object.

    &Person("David", 28) takes the address of this temporary object.

    However, temporary objects are destroyed at the end of the full expression (in this case, immediately after the push_back call).

    The vector vpp now stores a dangling pointer (a pointer to memory that's no longer valid).
    */
    for (vector<Person*>::iterator it = vpp.begin(); it != vpp.end(); it++) {
        cout << "Name: " << (*(*it)).name << ", Age: " << (*(*it)).age << endl;
        cout << "Name: " << (*it)->name << ", Age: " << (*it)->age << endl;
    }
}

// net vector
void test03() {
    cout << "Using vector of vectors of pointers to class: " << endl;
    vector<vector<Person*>> vvpp;
    
    vector<Person*> vvp1;
    Person p1("Alice", 30);
    Person p2("Bob", 25);
    Person p3("Charlie", 35);
    vvp1.push_back(&p1);
    vvp1.push_back(&p2);
    vvp1.push_back(&p3);
    
    vvpp.push_back(vvp1);
    
    vector<Person*> vvp2;
    Person p4("David", 28);
    Person p5("Eve", 22);
    vvp2.push_back(&p4);
    vvp2.push_back(&p5);
    
    vvpp.push_back(vvp2);

    for (vector<vector<Person*>>::iterator row = vvpp.begin(); row != vvpp.end(); row++) {
        for (vector<Person*>::iterator col = row->begin(); col != row->end(); col++) {
            cout << "Name: " << (*col)->name << ", Age: " << (*col)->age << endl;
        }
    }


}

int main() {
    test01();
    // test02();
    // test03();
    return 0;
}