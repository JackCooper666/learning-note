#include <iostream>
#include <string>
using namespace std;
template <typename T>
void reorder (T *a, int size){
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (a[j] >= a[j + 1]) {
                T temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}
template <typename T>
void printArray(T *a, int size) {
    for (int i = 0; i < size; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}
int main () {
    int pigs[] = {300, 350, 200, 400, 250};
    int size = sizeof(pigs) / sizeof(pigs[0]);
    reorder<int>(pigs, size);
    cout << "Sorted pigs: ";
    printArray<int>(pigs, size);
    cout << endl;

    char names[] = "fdsafsadf";
    int size_names = sizeof(names) / sizeof(names[0]) - 1; // Exclude null terminator
    reorder<char>(names, size_names);
    cout << "Sorted names: ";
    printArray<char>(names, size_names);
    cout << endl;
    
    string str = "hello";
    int size_str = str.size();
    char str_arr[size_str + 1]; // +1 for null terminator
    for (int i = 0; i < size_str; i++) {
        str_arr[i] = str[i];
    }
    str_arr[size_str] = '\0'; // Null-terminate the string
    reorder<char>(str_arr, size_str);
    cout << "Sorted string: ";
    printArray<char>(str_arr, size_str);
    cout << endl;


    return 0;
}