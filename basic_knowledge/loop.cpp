/*
int num = 0;
while (num < 10)
{
    cout << "num = " << num << endl;
    num++;
}

int num = 0;
do
{
    cout << num << endl;
    num++;

} while (num < 10);

//外层循环执行1次，内层循环执行1轮
for (int i = 0; i < 10; i++)
{
    for (int j = 0; j < 10; j++)
    {
        cout << "*" << " ";
    }
    cout << endl;
}
*/
#include <iostream>
#include <cmath>
using namespace std;
int main(){
    // int input;
    // int answer = 30;
    // while (1)
    // {
    //     cout << "type your answer" << endl;
    //     cin >> input;
    //     if(input == answer){
    //         break;
    //     }
    //     else if (input > answer){
    //         cout << "too large" << endl;
    //     }
    //     else if (input < answer){
    //         cout << "too small" << endl;
    //     }
    //     else{
    //         cout << "ERROR" << endl;
    //     }
    // }

    // 练习案例：水仙花数
    // **案例描述：**水仙花数是指一个 3 位数，它的每个位上的数字的 3次幂之和等于它本身
    // 例如：1^3 + 5^3+ 3^3 = 153
    // int num = 100;
    // int first,second,third;
    // int sum;
    // do
    // {
    //     num++;
    //     first = num / 100;
    //     second = (num / 10) % 10;
    //     third = num % 10;
    //     sum = pow(first, 3) + pow(second, 3) + pow(third, 3);
    //     if (sum == num)
    //     {
    //         cout << "水仙花数是：" << num << endl;
    //     }
    // } while (num <= 999);
    

    // 练习案例：敲桌子
    // 案例描述：从1开始数到数字100， 
    // 如果数字个位含有7，或者数字十位含有7，
    // 或者该数字是7的倍数，我们打印敲桌子，
    // 其余数字直接打印输出。
    // int second,thrid;
    // int remainder;    
    // for(int i = 1; i <= 100; i++){
    //     thrid = i%10;
    //     second = (i/10)%10;
    //     remainder = i%7;
    //     if (thrid == 7 || second == 7){
    //         cout << "i = " << i << endl;
    //         cout << "da" << endl;
    //     }
    //     else if (remainder == 0){
    //         cout << "i = " << i << endl;
    //         cout << "da" << endl;
    //     }
    //     else{}
    // }

    // 练习案例：打印乘法口诀表
    for (int i = 1; i <= 9; i++){
        for (int j = 1; j <= i; j++){
            cout << j << "*" << i << "=" << i*j << " ";
        }
        cout << endl;
    }

    return EXIT_SUCCESS;
}
