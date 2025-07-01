#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

void printlist(const list<int> &l){
    for(auto e:l){
        cout << e << " ";
    }
    cout << endl;
}

void test01(){
    // push_back(elem);//在容器尾部加入一个元素
    // pop_back();//删除容器中最后一个元素
    // push_front(elem);//在容器开头插入一个元素
    // pop_front();//从容器开头移除第一个元素
    // insert(pos,elem);//在pos位置插elem元素的拷贝，返回新数据的位置。
    // insert(pos,n,elem);//在pos位置插入n个elem数据，无返回值。
    // insert(pos,beg,end);//在pos位置插入[beg,end)区间的数据，无返回值。
    // clear();//移除容器的所有数据
    // erase(beg,end);//删除[beg,end)区间的数据，返回下一个数据的位置。
    // erase(pos);//删除pos位置的数据，返回下一个数据的位置。
    // remove(elem);//删除容器中所有与elem值匹配的元素。
    list<int> l;
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);

    l.push_front(1);
    l.push_front(2);
    printlist(l);

    l.pop_front();
    printlist(l);

    l.pop_back();
    printlist(l);

    // insert
    list<int>::iterator it = l.begin();
    l.insert(++it,1000);
    printlist(l);

    // erase
    l.erase(it);
    printlist(l);

    // in the code, why the result of the  l.erase(it); is 1 1000 4, 
    // why the 3 is deleted?  
    // the 1000 should be deleted
    // becuase the iterator is a pointer it pointing to the address of the 3 now.

    // delete
    l.push_back(10000);
    l.push_front(10000);
    printlist(l);
    l.remove(10000);
    printlist(l);

}

int main(){
    test01();
    return 0;
}