# set and multiset
**简介：**
- 所有元素都会在插入时自动被排序

**set和multiset区别**：
- set不可以插入重复数据，而multiset可以
- set插入数据的同时会返回插入结果，表示插入是否成功
- multiset不会检测数据，因此可以插入重复数据
```cpp
#include <set>

//set和multiset区别
void test01()
{
	set<int> s;
	pair<set<int>::iterator, bool>  ret = s.insert(10);
	if (ret.second) {
		cout << "第一次插入成功!" << endl;
	}
	else {
		cout << "第一次插入失败!" << endl;
	}

	ret = s.insert(10);
	if (ret.second) {
		cout << "第二次插入成功!" << endl;
	}
	else {
		cout << "第二次插入失败!" << endl;
	}
    
	//multiset
	multiset<int> ms;
	ms.insert(10);
	ms.insert(10);

	for (multiset<int>::iterator it = ms.begin(); it != ms.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}

int main() {

	test01();

	system("pause");

	return 0;
}
```
## set
- set容器插入数据时用insert
- set容器插入数据的数据会自动排序
- set容器默认排序规则为从小到大，掌握如何改变排序规则

```cpp
#include <set>

void printSet(set<int> & s)
{
	for (set<int>::iterator it = s.begin(); it != s.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

//构造和赋值
void test01()
{
	set<int> s1;

	s1.insert(10);
	s1.insert(30);
	s1.insert(20);
	s1.insert(40);
	printSet(s1);

	//拷贝构造
	set<int>s2(s1);
	printSet(s2);

	//赋值
	set<int>s3;
	s3 = s2;
	printSet(s3);
}

int main() {

	test01();

	system("pause");

	return 0;
}
```

**功能描述：**

- set容器进行插入数据和删除数据

**函数原型：**

- `insert(elem);` //在容器中插入元素。
- `clear();` //清除所有元素
- `erase(pos);` //删除pos迭代器所指的元素，返回下一个元素的迭代器。
- `erase(beg, end);` //删除区间[beg,end)的所有元素 ，返回下一个元素的迭代器。
- `erase(elem);` //删除容器中值为elem的元素。





# algorithm

下面是 **`.count()` 和 `.find()` 在 C++ 中的详细对比**，适用于 `set` / `unordered_set` / `map` / `unordered_map` 等容器。

---

## ✅ 相同点

|特性|`.count(x)`|`.find(x)`|
|---|---|---|
|判断元素是否存在|✅ 是|✅ 是|
|支持哪些容器|`set`, `map`, `unordered_*`|`set`, `map`, `unordered_*`|

---

## 🔍 不同点

| 项目     | `.count(x)`                | `.find(x)`                       |
| ------ | -------------------------- | -------------------------------- |
| 返回值类型  | `int`（通常是 0 或 1）           | `iterator`（指向元素，或 `end()` 表示不存在） |
| 判断方式   | `if (set.count(x))`        | `if (set.find(x) != set.end())`  |
| 访问元素的值 | ❌ 不能直接访问元素                 | ✅ 可通过 iterator 访问                |
| 性能（平均） | **O(1)** for `unordered_*` | **O(1)** for `unordered_*`       |