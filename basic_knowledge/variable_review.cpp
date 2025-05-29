#include <iostream>
using namespace std;
int main(){
    /*
    1. variable declare
    
    2. variable initalization 
    e.g. variable_type variable_name
    
    */
    // number
    int t;
    t = 0;
    // char and string
    char ch;
    ch = 'a';
    char str1[] = "Hello World";
    // bool
    bool log;
    log = true; // true, false
    // output
    cout << str1 << endl;

    // sizeof, get the size of the variable
    cout << "size fo the int is " << sizeof(t) << endl;

    return EXIT_SUCCESS;
}