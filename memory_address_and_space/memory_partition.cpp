#include<iostream>
using namespace std;
/*
​ 栈区：

​ 由编译器自动分配释放, 存放函数的参数值,局部变量等

​ 注意事项：不要返回局部变量的地址，栈区开辟的数据由编译器自动释放
*/
// int* func()
// {
// 	int a = 10;
// 	return &a; //??Segmentation fault (core dumped)
// }

// int main() {

// 	int *p;
// 	p = func();
// 	cout << *p << endl;
// 	cout << *p << endl;

// 	// system("pause");

// 	return 0;
// }




/*
​ 堆区：

​ 由程序员分配释放,若程序员不释放,程序结束时由操作系统回收

​ 在C++中主要利用new在堆区开辟内存

​ C++中利用==new==操作符在堆区开辟数据

​ 堆区开辟的数据，由程序员手动开辟，手动释放，释放利用操作符 ==delete==

​ 语法： new 数据类型

​ 利用new创建的数据，会返回该数据对应的类型的指针
*/

// int* func()
// {
// 	int* a = new int(10); // the "new" gives an address
// 	return a;
// }

// int main() {

// 	int *p = func();

// 	cout << *p << endl;
// 	cout << *p << endl;

// 	//利用delete释放堆区数据
// 	delete p;

// 	//cout << *p << endl; //报错，释放的空间不可访问

// 	// system("pause");

// 	return 0;
// }

// 开辟数组

int main(){
	int* arr = new int[10]; 
	// be careful, here is "[]", not "()", which define the size of the array
	for (int i = 0; i < 10; i++)
	{
		cout << arr[i] << endl;
	}
	cout << "-----------------" << endl;
	for (int i = 0; i < 10; i++){
		arr[i] = i + 100;
	}
	for (int i = 0; i < 10; i++)
	{
		cout << arr[i] << endl;
	}
	cout << "-----------------" << endl;

	//释放数组 delete 后加 []
	delete[] arr;
	return 0;
}

