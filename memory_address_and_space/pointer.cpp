#include "pointer_function.h"

int main(){
    /*
    7.1 指针的基本概念
    指针的作用： 可以通过指针间接访问内存
    内存编号是从0开始记录的，一般用十六进制数字表示
    可以利用指针变量保存地址
    */

    /*
    pointer variable initialization:

    1.
    int *p = &a;
    
    2.
    int *p;
    int a = 10;
    p = &a;

    if you use this, this is still unkown
    int *p;
    int a = 10;
    *p = a;
    */



    int a = 10;

    //指针定义语法： 数据类型 * 变量名 ;
    int* p; 
    // declare the pointer
    p = &a; 
    // accosiate the address of variable a into the pointer

    cout << &a << endl;
    cout << p << endl;

    cout << *p << endl; 
    // read the content in the address where the pointer pointed

    cout << sizeof(p) << endl;
    cout << sizeof(char *) << endl;
    cout << sizeof(float *) << endl;
    cout << sizeof(double *) << endl;

    /*
    7.4 空指针和野指针
        空指针：指针变量指向内存中编号为0的空间
        **用途：**初始化指针变量
        **注意：**空指针指向的内存是不可以访问的
    */
    //指针变量p指向内存地址编号为0的空间
//	int * p_null = NULL;

	//访问空指针报错 
	//内存编号0 ~255为系统占用内存，不允许用户访问
//	cout << *p_null << endl;

    // 野指针
    //指针变量p指向内存地址编号为0x1100的空间
//	int * p_bad = (int *)0x1100;

	//访问野指针报错 
//	cout << *p_bad << endl;

    //总结：空指针和野指针都不是我们申请的空间，因此不要访问。

    /*
    7.5 const修饰指针
        const修饰指针有三种情况
        const修饰指针 --- 常量指针
        const修饰常量 --- 指针常量
        const即修饰指针，又修饰常量
    */
   int a_cp = 10;
   int b_cp = 20;
   
   //const修饰的是指针，指针指向可以改，指针指向的值不可以更改
   const int * const_p = &a_cp;
   cout << *const_p << endl;
   const_p = &b_cp;
   cout << *const_p << endl;
   //*const_p = 100;  报错
	

	//const修饰的是常量，指针指向不可以改，指针指向的值可以更改
	int * const p_const = &a_cp;
	//p_const = &b_cp; //错误
	*p_const = 100; //正确

    //const既修饰指针又修饰常量
	const int * const const_p_const = &a;
	//const_p_const = &b; //错误
	//*const_p_const = 100; //错误

    // 7.6 指针和数组
    // **作用：**利用指针访问数组中元素
    int arr_p[] = {1, 2, 3, 4, 5};
    int* p_arr = arr_p;
    cout << "the first element in the array" << arr_p[0] << endl;
    cout << "the first element is the array" << *p_arr << endl;

    int* temp = p_arr;
    for(int i = 0; i < 5; i++){
        cout << *temp << endl;
        temp++;
    }

    /* function with pointer*/
    // **作用：**利用指针作函数参数，可以修改实参的值
    int a_swap = 10;
    int b_swap = 20;
    cout << "before swap" << endl;
    cout << "a_swap = " << a_swap << endl;
    cout << "b_swap = " << b_swap << endl;
    // swap_without_p(a_swap, b_swap);
    // cout << "after swap" << endl;
    // cout << "a_swap = " << a_swap << endl;
    // cout << "b_swap = " << b_swap << endl;
    swap_with_p(&a_swap, &b_swap);
    cout << "after swap" << endl;
    cout << "a_swap = " << a_swap << endl;
    cout << "b_swap = " << b_swap << endl;

    int arr_for_pointer[] = {4, 2,3, 5, 1};
    int len = sizeof(arr_for_pointer) / sizeof(arr_for_pointer[0]);
    printArrary(arr_for_pointer, len);
    bubbleSort(arr_for_pointer, len);
    cout << "after bubble sort" << endl;
    printArrary(arr_for_pointer, len);

    return EXIT_SUCCESS;
}
void swap_without_p(int a, int b){
    int temp = a;
    a = b;
    b = temp;
}
void swap_with_p(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
void bubbleSort(int arr[], int len){
    for(int i = 0; i < len -1; i++){
        for(int j=0;j < len - 1 - i; j++){
            if(arr[j] > arr[j + 1]){
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
void printArrary(int arr[], int len){
    for(int i = 0; i < len; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}