#include <iostream>
using namespace std;
int main(){
    /*
    bool variable
    bool log;
    "and" &&
    "or" ||
    "not" !
    */

    /*
    ==, !=, >, <, >=, <=
    */
    
    /*
    if (condition){
    }
    else if (condition){
    }
    else{
    }
    */
    // 排序问题

    // float a, b, c;
    // float temp;
    // char pig;
    // cout << "please input the weight of the three pigs" << endl;
    // cin >> a;
    // cin >> b;
    // cin >> c;
    // cout << "pig a:" << a << endl;
    // cout << "pig b:" << b << endl;
    // cout << "pig c:" << c << endl;
    // if(a >= b){
    //     temp = a;
    //     pig = 'a';
    // }
    // else if (a < b){
    //     temp = b;
    //     pig = 'b';
    // }
    // if(temp >= c){
    //     cout << "weightest one is " << pig << endl;
    // }
    // else{
    //     temp = c;
    //     pig = 'c';
    //     cout << "weightest one is " << pig <<endl;
    // }

    /*
    三目运算符
    表达式1 ? 表达式2 ：表达式3
    如果表达式1的值为真，执行表达式2，并返回表达式2的结果；
    如果表达式1的值为假，执行表达式3，并返回表达式3的结果。
    */
    int a = 10, b = 100, c;
    c = a > b ? a : b;
    cout << "c = " << c << endl;
    
    (a > b ? a : b) = 50;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
    /*
    switch(表达式)
    {

        case 结果1：执行语句;break;

        case 结果2：执行语句;break;

        ...

        default:执行语句;break;

    }
    */
   int score;
   cout << "socre the movie" << endl;
   cin >> score;
   switch (score)
    {
        case 10:
        case 9:
            cout << "classic" << endl;
        break;
        case 8:
            cout << "very good" << endl;
        break;
        case 7:
        case 6:
            cout << "normal" << endl;
        break;
        default:
            cout << "bad" << endl;
        break;
    }
    return EXIT_SUCCESS;
}