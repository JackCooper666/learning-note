#include <iostream>
using namespace std;

// int main(){
//     /*
//          2.1 引用的基本使用
//          **作用： **给变量起别名
//          语法： 数据类型 &别名 = 原名
//     */
//     int a = 10;
//     int &b = a; 
//     // & get the address of b 
//     // and sign the address of a into that of b
//     cout << "a = " << a << endl;
// 	cout << "b = " << b << endl;

// 	b = 100;

// 	cout << "a = " << a << endl;
// 	cout << "b = " << b << endl;

//     a = 200;

//     cout << "a = " << a << endl;
// 	cout << "b = " << b << endl;

    
//     return EXIT_SUCCESS;
// }

// int main(){
//     /*
//         2.2 引用注意事项
//         引用必须初始化
//         引用在初始化后，不可以改变
//     */
//     int a = 10;
//     int b = 20;
//     //int &c; //错误，引用必须初始化
//     int &c = a; //一旦初始化后，就不可以更改
//     c = b; //这是赋值操作，不是更改引用
    
//     cout << "a = " << a << endl;
// 	cout << "b = " << b << endl;
// 	cout << "c = " << c << endl;


//     return EXIT_SUCCESS;
// }

/*
2.3 引用做函数参数
**作用：**函数传参时，可以利用引用的技术让形参修饰实参
**优点：**可以简化指针修改实参
*/

// void Swap1(int a, int b){
//     int temp;
//     temp = a;
//     a = b;
//     b = temp;
// }
// void Swap2(int *a, int *b){
//     int temp;
//     temp = *a;
//     *a = *b;
//     *b = temp;
// }
// void Swap3(int &a, int &b){
//     int temp;
//     temp = a;
//     a = b;
//     b = temp;
// }

// int main(){
//     int a = 10;
//     int b = 20;
//     cout << "org a and b" << endl;
//     cout << "a: " << a;
//     cout << "b: " << b <<endl;
//     Swap1(a,b);
//     cout << "Swap1" << endl;
//     cout << "a: " << a;
//     cout << " b: " << b <<endl;
//     Swap2(&a, &b);
//     cout << "Swap2" << endl;
//     cout << "a: " << a;
//     cout << " b: " << b <<endl;
//     Swap3(a,b);
//     cout << "Swap3" << endl;
//     cout << "a: " << a;
//     cout << " b: " << b <<endl;
// }

// /*
// 2.4 引用做函数返回值
// 作用：引用是可以作为函数的返回值存在的
// 注意：不要返回局部变量引用
// 用法：函数调用作为左值
// */

// //返回局部变量引用
// int& add1(int a, int b){
//     int sum = a + b; //局部变量
//     return sum;
// }
// int& add2(int a, int b){
//     static int sum = a + b;
//     return sum;
// }

// int main(){

//     //不能返回局部变量的引用
//     // int& ref1 = add1(10,20);
//     // cout << "ref1 = " << ref1 << endl;
//     // this because the & is a pointer actually, 
//     // it needs to point to a real address,
//     // but the address of the local variable will be deleted after the function done.

//     int &ref2 = add2(10,20);
//     cout << "ref2 = " << ref2 << endl;

//     add2(2,3)++;
//     cout << "ref2 = " << ref2 << endl;
//     /*
//     result: 
//         zewen@zewen-Lenovo-Legion-Y7000-2020:~/cpp_practise/output$ ./"citation"
//         ref2 = 30
//         ref2 = 31 ??
//     */
//     // quite strange.
//     return EXIT_SUCCESS;
// }


/*
2.6 常量引用
**作用：**常量引用主要用来修饰形参，防止误操作
在函数形参列表中，可以加==const修饰形参==，防止形参改变实参
*/
// the formal parameter using the &, the actual parameter will be changed, 
// if the formal parameter in the function changes, 
// which is quite dangerous

void showValue(const int &v){
    // v++; // this line cuase the failure of compile
    cout << v <<endl;
}
int main(){
    int a = 10;
    showValue(a);
    return EXIT_SUCCESS;
}