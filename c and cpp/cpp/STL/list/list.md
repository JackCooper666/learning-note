list consists of nodes
# single direction list
node consist of its data and a pointer pointing to the address of the next node.
![[list.png]]
the advantages of the the list is that:
1. user can insert or delete nodes at any position

the disadvantages of the list is that:
1. the traversal speed is slower than the that of the array
2. space consumption is larger than that of the array

# the list in the STL
The STL's list is bio-direction list.
The node of it consists of three things: the data, the next pointer pointing to the address of the next node, the previous pointer pointing to the address of the previous node.
![[bio_direction_list.jpg]]

`push_front()`: push node at the top
`pop_front()`: pop the node at the top
`front()`: get the node at the top
`push_back()`: push node at the end
`pop_back()`: pop the node at the end
`back()`: get the node at the end

由于链表的存储方式并不是连续的内存空间，因此链表list中的迭代器只支持前移和后移，属于**双向迭代器**
## construct list
- `list<T> lst;` //list采用采用模板类实现,对象的默认构造形式：
- `list(beg,end);` //构造函数将[beg, end)区间中的元素拷贝给本身。
- `list(n,elem);` //构造函数将n个elem拷贝给本身。
- `list(const list &lst);` //拷贝构造函数。
```cpp
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
```
## assignment operation