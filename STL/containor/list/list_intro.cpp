#include <iostream>
#include <list>

using namespace std;
void printlist(const list<int> &mylist){
    for(const auto element : mylist){
        cout << element << " ";
    }
    cout << endl;
    // or using the iterator read-only access
    for(list<int>::const_iterator it = mylist.begin(); it != mylist.end(); ++it){
        cout << *it << " ";
    }
    cout << endl;
}
void test01(){
    list<int> mylist;
    mylist.push_back(10);
    mylist.push_back(20);
    mylist.push_back(30);
    mylist.push_front(5);
    mylist.push_front(1);
    cout << "List after adding elements: " << endl;
    printlist(mylist);
    list<int> mylist2(mylist); // Copy constructor
    cout << "List after copy construction: " << endl;
    printlist(mylist2);
    list<int> mylist3(mylist.begin(),mylist.end()); // Copy assignment
    cout << "List after copy assignment: " << endl;
    printlist(mylist3);
    // Initializing a list with 10 elements, each with the value 100
    list<int> mylist4(10,100);
    cout << "List initialized with 10 elements of value 100: " << endl;
    printlist(mylist4);
}

int main(){
    test01();
    return 0;
}