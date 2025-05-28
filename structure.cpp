#include "structure_lib.h"

/*
8.2 结构体定义和使用
语法：struct 结构体名 { 结构体成员列表 }；

通过结构体创建变量的方式有三种：

struct 结构体名 变量名
struct 结构体名 变量名 = { 成员1值 ， 成员2值...}
定义结构体时顺便创建变量
*/

int main(){
    student stu1;
    stu1.name = "zhangsan";
    stu1.age = 20;
    stu1.score = 90.5;
    cout << "name: " << stu1.name << endl;
    cout << "age: " << stu1.age << endl;
    cout << "score: " << stu1.score << endl;
    student stu2 = {"lisi", 22, 85.0};
    cout << "name: " << stu2.name << endl;
    cout << "age: " << stu2.age << endl;
    cout << "score: " << stu2.score << endl;
    cout << "-------------------------" << endl;


    // structure array
    cout << "----structure array----" << endl;
    student stu_arr[3] = 
    {
        {"zhangsan", 20, 90.5}, 
        {"lisi", 22, 85.0}, 
        {"wangwu", 21, 88.0}
    };
    
    for(int i = 0; i < 3; i++){
        cout << "name: " << stu_arr[i].name << endl;
        cout << "age: " << stu_arr[i].age << endl;
        cout << "score: " << stu_arr[i].score << endl;
    }
    cout << "-------------------------" << endl;

    // structure pointer
    cout << "----structure pointer----" << endl;
    student* p_stu = &stu1;
    p_stu->name = "zhangsing";
    cout << "name: " << p_stu->name << endl;
    cout << "age: " << p_stu->age << endl;
    cout << "score: " << p_stu->score << endl;
    cout << "-------------------------" << endl;


    // neted structure
    cout << "----neted structure----" << endl;
    teacher t1;
    t1.name = "zhanglaoshi";
    t1.age = 40;
    t1.salary = 10000.0;
    t1.stu.name = "zhangsan";
    t1.stu.age = 20;
    t1.stu.score = 90.5;
    cout << "teacher name: " << t1.name << endl;
    cout << "teacher age: " << t1.age << endl;
    cout << "teacher salary: " << t1.salary << endl;
    cout << "student name: " << t1.stu.name << endl;
    cout << "-------------------------" << endl;

    // function with structure
    cout << "----function with structure----" << endl;
    student stu3 = {"wangwu", 21, 88.0};
    printStudent_variable_transfer(stu3);
    cout << "name: " << stu3.name << endl;
    cout << "age: " << stu3.age << endl;
    cout << "score: " << stu3.score << endl;
    cout << "-------------------------" << endl;
    Student_info_edit(&stu3);
    cout << "name: " << stu3.name << endl;
    cout << "age: " << stu3.age << endl;
    cout << "score: " << stu3.score << endl;
    cout << "-------------------------" << endl;

    // const structure
    cout << "----const structure----" << endl;
    student stu4 = {"wangermazi", 20, 90.5};
    printStudent_const_variable_transfer(&stu4);

}
void printStudent_variable_transfer(student stu){
    stu.name = "lisi";
    cout << "name: " << stu.name << endl;
    cout << "age: " << stu.age << endl;
    cout << "score: " << stu.score << endl;
}
void Student_info_edit(student* stu){
    stu->name = "lisi";
    cout << "name: " << stu->name << endl;
    cout << "age: " << stu->age << endl;
    cout << "score: " << stu->score << endl;
}
void printStudent_const_variable_transfer(const student* stu){
    //stu->age = 100; //操作失败，因为加了const修饰
	cout << "name:" << stu->name << " age:" << stu->age << " score" << stu->score << endl;
}