# map

对于map的底层原理，是通过红黑树（一种非严格意义上的平衡二叉树）来实现的，因此map内部所有的数据都是有序的，map的查询、插入、删除操作的时间复杂度都是O(logn)。


declare and initialise a map
```cpp
#include <map>
map<int, int> mp; // similar with the dictionary in python
// the first int is for the key
// the second int is for the value

mp[10001] = 82;
mp[10002] = 83;
mp[10003] = 84;

cout << mp[10001] << endl;
```

the algorithm in the map STL
`.find(key)` find whether the key in the map
`.end()` return the end address of the map

go through the map elements
1. by the auto
```cpp
auto it =  mp.begin();
for (;it!=mp.end();it++){
	cout << (*it).first << " " << (*it).second << " ";
}

// or 

for (auto it : mp) {
    cout << it.first << " " << it.second << " ";
}
// 1. `it` is not an iterator, but actually a `pair<const int, int>` (the key-value pair) 
// 2. The loop automatically handles moving to the next element 
// 3. You access the key and value directly with `it.first` and `it.second`
// first is the key, second is the value.
```
2. by the iterator
```cpp
map<int,int>::iterator it;
for (it = mp.begin();it!=mp.end();it++){
	cout << (*it).first << " " << (*it).second << " ";
	// first is the key, second is the value.
}
```

# unordered_map

unordered_map和map类似，都是存储的key-value的值，可以通过key快速索引到value。不同的是unordered_map不会根据key的大小进行排序，存储时是根据key的hash值判断元素是否相同，即unordered_map内部元素是无序的。unordered_map的底层是一个防冗余的哈希表（开链法避免地址冲突）。
```cpp
#include <unordered_map>
#include <iostream>
using namespace std;
int main(){
// declare and initialise an unordered map
unordered_map<int,int> m;
m['a'] = 9;
m['b'] = 10;
m['c'] = 11;
m[' '] = 12;
m['z'] = 13;
cout << m.size() << endl;
it (m.count(' ') == 1){
 cout << m[' '] << endl;
}
for (auto it = m.begin(); it!=m.end();it++){
 cout << it->first << " " << it->second << " " << endl;
}
return 0;
}


```

the algorithm in the unordered map STL
```cpp
m.size();
m.insert();
m.find(key);
m.count(key);
m.erase(key);
m[key];
```

| Method     | Returns                     | Use Case                                   |
| ---------- | --------------------------- | ------------------------------------------ |
| `.find()`  | Iterator (can access value) | When you need the element (key-value pair) |
| `.count()` | `0` or `1`                  | When you only need to check existence      |