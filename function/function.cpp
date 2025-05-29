#include "function_lib.h"
// the " " is for the local file
// the < > is for the system file

int main(){
    int a, b;
    a = 10;
    b = 30;
    int c;
    c = max(a,b);
    cout << "the max is " << c << endl;
}
int max(int a, int b){
    return (a > b) ? a : b;
}