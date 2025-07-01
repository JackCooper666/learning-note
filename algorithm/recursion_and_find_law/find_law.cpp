#include <iostream>
#include <cmath>
using namespace std;

void stacking_boxes();
void monkey_and_banana();
float first_n_term_sum(int n);
int numerator(int n);
int denominator(int n);

int main(){
    // monkey_and_banana();
    float sum = 0.0;
    sum = first_n_term_sum(20);
    cout << "Sum of first 20 terms = " << sum << endl;
    return 0;
}
void stacking_boxes() {
    int a[110] = {0};
    a[1] = 1;
    int n = 100;
    for(int i = 1; i <= n; i++) {
        a[i] = i + a[i - 1];
        cout << "a[" << i << "] = " << a[i] << endl;
    }
    
    int sum = 0;
    for(int i = 1; i <= n; i++) {
        sum += a[i];
    }
    cout << "Sum of a[1] to a[" << n << "] = " << sum << endl;
}

void monkey_and_banana() {
    int sum[10] = {0};
    sum[1] = 1;
    for(int i = 2; i <= 10; i++){
        sum[i] = sum[i - 1] + 3 * pow(2, i - 2);
        cout << "sum[" << i << "] = " << sum[i] << endl;
    }
}

int numerator(int n){
    int res;
    if(n == 1){
        res = 1;
    }
    else {
        res = denominator(n - 1);
    }
    return res;
}
int denominator(int n){
    int res;
    if(n == 1){
        res = 1;
    }
    else {
        res = numerator(n - 1) + denominator(n - 1);
    }
    return res;
}

float first_n_term_sum(int n){
    float sum = 0.0;
    for(int i = 1; i <= n; i++){
        sum += static_cast<float>(numerator(i)) / denominator(i);   
    }
    return sum;
}