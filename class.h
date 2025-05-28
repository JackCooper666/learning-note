#include<iostream>
using namespace std;

const string schoole_name = "NUS";


class Student
{
    public: // public variable elements
    string univeristy; // write and read only
    // the public variable and behavirouses can be accessed in programs

    private:
    // the private and protected variables and behavirouses 
    // can only be accessed by the functions in the public
    int stu_id; // write only
    string stu_name; // read and write
    string stu_lover; // write only
    int Age; // read and write only


    public: // public behavirouses
    void setid(int id){
        stu_id = id;
    }

    void setname(string name){
        stu_name = name;
    }
    void readname(){
        cout << "student name is " << stu_name << endl;
    }

    void setlover(string lover){
        stu_lover = lover;
    }

    void setage(int age){
        Age = age;
    }
    void readage(){
        cout << "student age is " << Age << endl;
    }

};