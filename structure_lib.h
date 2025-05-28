#include <iostream>
using namespace std;
struct student
{
    string name;
    int age;
    float score;
};
// neted structure
struct teacher
{
    string name;
    int age;
    float salary;
    struct student stu; // nested structure
};

void printStudent_variable_transfer(student stu);
void Student_info_edit(student* stu);
void printStudent_const_variable_transfer(const student* stu);

