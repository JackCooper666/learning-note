#include <iostream>
// cpp可以自己调自己，与C不同，cpp不允许main()调用自己，这种功能被称为递归。
int accumulatino(int n);
int geometricprogression(int n);
int factorial(int n);
int fibnacci(int n);

int main() {
int n = 6;
    std::cout << "accumulatino(" << n << ") = " << accumulatino(n) << std::endl;
    std::cout << "geometricprogression(" << n << ") = " << geometricprogression(n) << std::endl;
    std::cout << "factorial(" << n << ") = " << factorial(n) << std::endl;
    std::cout << "fibnacci(" << n << ") = " << fibnacci(n) << std::endl;
    // 输出：accumulatino(6) = 19
    // 计算过程：1 + 3 + 3 + 3 + 3 + 3 = 19
    return 0;
}
int accumulatino(int n) {
    // base case
    if (n == 1){
        return 1;
    }
    // recursive case
    else{
        return accumulatino(n - 1) + 3;
    }
}
// geometricprogression
int geometricprogression(int n){
    //base case
    if (n == 1){
        return 2;
    }
    // recursive case
    else{
        return geometricprogression(n - 1) * 2;
    }
}
// fastorial
int factorial(int n) {
    if(n == 1 || n == 0) {
        return 1; // base case
    } else {
        return n * factorial(n - 1); // recursive case
    }
}

// fibnacci
int fibnacci(int n) {
    if ( n ==1 || n == 2) {
        return 1; // base case
    } else {
        return fibnacci(n - 1) + fibnacci(n - 2); // recursive case
    }
}