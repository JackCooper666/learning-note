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

```cpp
#include<iostream>
#include<map>
#include<string>
 
using namespace std;
 
int main()
{
	// 构造函数
	map<string, int> dict;
	
	// 插入数据的三种方式
	dict.insert(pair<string,int>("apple",2));
	dict.insert(map<string, int>::value_type("orange",3));
	dict["banana"] = 6;
 
	// 判断是否有元素
	if(dict.empty())
		cout<<"该字典无元素"<<endl;
	else
		cout<<"该字典共有"<<dict.size()<<"个元素"<<endl;
 
	// 遍历
	map<string, int>::iterator iter;
	for(iter=dict.begin();iter!=dict.end();iter++)
		cout<<iter->first<<ends<<iter->second<<endl;
 
	// 查找
	if((iter=dict.find("banana"))!=dict.end()) //  返回一个迭代器指向键值为key的元素，如果没找到就返回end()
		cout<<"已找到banana,其value为"<<iter->second<<"."<<endl;
	else
		cout<<"未找到banana."<<endl;
 
	if(dict.count("watermelon")==0) // 返回键值等于key的元素的个数
		cout<<"watermelon不存在"<<endl;
	else
		cout<<"watermelon存在"<<endl;
	
	pair<map<string, int>::iterator, map<string, int>::iterator> ret;
	ret = dict.equal_range("banana"); // 查找键值等于 key 的元素区间为[start,end)，指示范围的两个迭代器以 pair 返回
	cout<<ret.first->first<<ends<<ret.first->second<<endl;
	cout<<ret.second->first<<ends<<ret.second->second<<endl;
 
	iter = dict.lower_bound("boluo"); // 返回一个迭代器，指向键值>=key的第一个元素。
	cout<<iter->first<<endl;
	iter = dict.upper_bound("boluo"); // 返回一个迭代器，指向值键值>key的第一个元素。
	cout<<iter->first<<endl;
	return 0;
}
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

```cpp
#include<string>  
#include<iostream>  
#include<unordered_map>
using namespace std;  
  
int main()
{
	unordered_map<string, int>  dict; // 声明unordered_map对象
	
	// 插入数据的三种方式
	dict.insert(pair<string,int>("apple",2));
	dict.insert(unordered_map<string, int>::value_type("orange",3));
	dict["banana"] = 6;
	
	// 判断是否有元素
	if(dict.empty())
		cout<<"该字典无元素"<<endl;
	else
		cout<<"该字典共有"<<dict.size()<<"个元素"<<endl;
	
	// 遍历
	unordered_map<string, int>::iterator iter;
	for(iter=dict.begin();iter!=dict.end();iter++)
		cout<<iter->first<<ends<<iter->second<<endl;
	
	// 查找
	if(dict.count("boluo")==0)
		cout<<"can't find boluo!"<<endl;
	else
		cout<<"find boluo!"<<endl;
	
	if((iter=dict.find("banana"))!=dict.end())
		cout<<"banana="<<iter->second<<endl;
	else
		cout<<"can't find boluo!"<<endl;
	
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