#include "pure_virtual_func_and_abstract_class_secnario.h"
int main () {
    Abstractdrink* drink1 = new Tea();
    drink1->make();
    delete drink1;

    Abstractdrink* drink2 = new Coffee();
    drink2->make();
    delete drink2;

    return 0;
}