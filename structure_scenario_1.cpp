/*
案例描述：

学校正在做毕设项目，每名老师带领5个学生，总共有3名老师，需求如下

设计学生和老师的结构体，其中在老师的结构体中，有老师姓名和一个存放5名学生的数组作为成员

学生的成员有姓名、考试分数，创建数组存放3名老师，通过函数给每个老师及所带的学生赋值

最终打印出老师数据以及老师所带的学生数据。
*/
#include <iostream>
using namespace std;
#include <string>
#include <ctime>

struct Student
{
    string name;
    int score;
};

struct Teacher
{
    string name;
    Student stu[5]; // 5 students
};
void allocatestudent(Teacher t[], int len)
{
    string teacher_name;
    string student_name;
    string teacher_name_tip = "teacher";
    string student_name_tip = "student";
    string nameseed = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    int student_score;
    
    for (int i = 0; i < len; i++)
    {
        // cout << "-------------------------" << endl;
        // cout << "teachers's name: ";
        teacher_name = teacher_name_tip + nameseed[i];
        // cout << teacher_name << endl;
        t[i].name = teacher_name; // allocates teachers
        
        // allocates students
        for (int j = 0; j < 5; j++)
        {
            // cout << "students's name: ";
            student_name = student_name_tip + nameseed[j];
            // cout << student_name << endl;
            t[i].stu[j].name = student_name; // allocates students
            // random score
            // cout << "students's score: ";
            student_score = rand() % 100 + 1; // random score
            // cout << student_score << endl;
            t[i].stu[j].score = student_score; // allocates students
        }

    }

}
void printStudent(Teacher t[], int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << "-------------------------" << endl;
        cout << "teachers's name: " << t[i].name << endl;
        for (int j = 0; j < 5; j++)
        {
            cout << "students's name: " << t[i].stu[j].name << endl;
            cout << "students's score: " << t[i].stu[j].score << endl;
        }
    }
}

int main(){
    srand((unsigned int)time(NULL)); //随机数种子 头文件 #include <ctime>
    Teacher teachers[3]; // 3 teachers
    int len;
    len = sizeof(teachers) / sizeof(teachers[0]); // 3 teachers
    cout << "the number of teachers: " << len << endl;
    // allocates teachers
    allocatestudent(teachers, len);
    // print teachers
    printStudent(teachers, len);

    return EXIT_SUCCESS;
}