#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

class list_assign{
    public:
    void prinslist(const list<int> &l);
};
void list_assign::prinslist(const list<int> &l){
    for(auto e:l){
        cout << e << endl;
    }
    cout << "------------------------" << endl;
}
int main(){
    list<int> l1;
    list_assign la;

    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);
    l1.push_back(4);
    l1.push_back(5);
    cout << "l1" << endl;
    la.prinslist(l1);
    
    // list assignment
    
    // l2  = l1
    list<int> l2;
    l2 = l1;
    cout << "l2" << endl;
    la.prinslist(l2);
    
    // .assign(start position, end position)
    list<int> l3;
    l3.assign(l2.begin(),l2.end());
    cout << "l3" << endl;
    la.prinslist(l3);

    // assign(n,m) // n个m
    list<int> l4;
    l4.assign(4,5);
    cout << "l4" << endl;
    la.prinslist(l4);

    // list swap
    l2.swap(l4);
    cout << "l4" << endl;
    la.prinslist(l4);
    cout << "l2" << endl;
    la.prinslist(l2); 



    return 0;
}