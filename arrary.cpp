/*
一维数组定义的三种方式：
数据类型 数组名[ 数组长度 ];
数据类型 数组名[ 数组长度 ] = { 值1，值2 ...};
数据类型 数组名[ ] = { 值1，值2 ...};
*/
#include<iostream>
using namespace std;
int main(){
    //定义方式1
	//数据类型 数组名[元素个数];
	int score[10];

    score[0] = 10;
    score[1] = 99;
    score[2] = 85;

    cout << score[0] << endl;
    cout << score[1] << endl;
    cout << score[2] << endl;

    //第二种定义方式
	//数据类型 数组名[元素个数] =  {值1，值2 ，值3 ...};
	//如果{}内不足10个数据，剩余数据用0补全
    int score2[10] = {100,20,30,50,40,6,80,20,40,60};

    //一个一个输出太麻烦，因此可以利用循环进行输出
	for (int i = 0; i < 10; i++)
	{
		cout << score2[i] << endl;
	}

    //定义方式3
	//数据类型 数组名[] =  {值1，值2 ，值3 ...};
	int score3[] = { 100,90,80,70,60,50,40,30,20,10 };

	for (int i = 0; i < 10; i++)
	{
		cout << score3[i] << endl;
    }

    /*
    一维数组名称的用途：    
        可以统计整个数组在内存中的长度
        可以获取数组在内存中的首地址
    */
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    cout << "the size of the whole array " << sizeof(arr) << endl;
    cout << "the size of the first element in the array " << sizeof(arr[0]) << endl;
    cout << "the num of elements in the array " << sizeof(arr)/sizeof(arr[0]) << endl;

    /*
    practise:
    练习案例1：五只小猪称体重
    案例描述：
    在一个数组中记录了五只小猪的体重，如：int arr[5] = {300,350,200,400,250};
    找出并打印最重的小猪体重。
    */
    int pigs[5] = {300,350,200,400,250};
    int num_pigs = sizeof(pigs)/sizeof(pigs[0]);
    int max_w = 0;
    for (int i = 0; i < num_pigs; i++){
        // for (int j = i; j < num_pigs; j++){
        //     if(pigs[j] >= pigs[i]){
        //         temp = pigs[j];
        //     }
        // }
        if (pigs[i] >= max_w){
            max_w = pigs[i];
        }
    }
    cout << "the heaviest one is " << max_w << endl;
    
    /*
    **练习案例2：**数组元素逆置
    **案例描述：**请声明一个5个元素的数组，并且将元素逆置.
    (如原数组元素为：1,3,2,5,4;逆置后输出结果为:4,5,2,3,1);
    */
   for (int i = 0; i < num_pigs - 1; i++){
        for (int j = 0; j > num_pigs - i - 1; j++){
            if (pigs[j] < pigs[j + 1]){
                int temp = pigs[j];
                pigs[j] = pigs[j + 1];
                pigs[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < num_pigs; i++){
        cout << pigs[i] << " ";
    }

    /*
    5.3.1 二维数组定义方式
        二维数组定义的四种方式：
        数据类型 数组名[ 行数 ][ 列数 ];
        数据类型 数组名[ 行数 ][ 列数 ] = { {数据1，数据2 } ，{数据3，数据4 } };
        数据类型 数组名[ 行数 ][ 列数 ] = { 数据1，数据2，数据3，数据4};
        数据类型 数组名[ ][ 列数 ] = { 数据1，数据2，数据3，数据4};
        建议：以上4种定义方式，利用==第二种更加直观，提高代码的可读性==
    */
   cout << endl; // change the line
   // the endl is to change the line
   int arr2d[2][3] = 
   { 
        {1,2,3}, 
        {4,5,6} 
    };

    // Print elements of arr2d to
    // use the variable and avoid unused warning
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            cout << arr2d[i][j] << " ";
        }
        cout << endl; // change the line
    }
    
    cout << "二维数组大小： " << sizeof(arr2d) << endl;
	cout << "二维数组一行大小： " << sizeof(arr2d[0]) << endl;
	cout << "二维数组元素大小： " << sizeof(arr2d[0][0]) << endl;

	cout << "二维数组行数： " << sizeof(arr2d) / sizeof(arr2d[0]) << endl;
	cout << "二维数组列数： " << sizeof(arr2d[0]) / sizeof(arr2d[0][0]) << endl;

	//地址
	cout << "二维数组首地址：" << arr2d << endl;
	cout << "二维数组第一行地址：" << arr2d[0] << endl;
	cout << "二维数组第二行地址：" << arr2d[1] << endl;

	cout << "二维数组第一个元素地址：" << &arr2d[0][0] << endl;
	cout << "二维数组第二个元素地址：" << &arr2d[0][1] << endl;

    /*
    二维数组应用案例
    考试成绩统计：

    案例描述：有三名同学（张三，李四，王五），在一次考试中的成绩分别如下表，请分别输出三名同学的总成绩

           语文 数学 英语
    张三	100	100	100
    李四	90	50	100
    王五	60	70	80
    */
    int score2d[3][3] = 
    { 
        {100,100,100}, 
        {90,50,100}, 
        {60,70,80} 
    };

    string name[3] = {"张三", "李四", "王五"};
    int sum[3] = {0, 0, 0};
    for (int i = 0; i<3;i++){
        for(int j = 0;j<3;j++){
            sum[i] += score2d[i][j];
        }
    }
    for (int i = 0; i<3;i++){
        cout << name[i] << "的总成绩是：" << sum[i] << endl;
    }
    return EXIT_SUCCESS;
}