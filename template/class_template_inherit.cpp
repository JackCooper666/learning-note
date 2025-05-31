#include "class_template_inherit.hpp"
void test01(){
    Son son("John", 20, 1000.0, "Michael", 50, 50000.0);
    // Output:
    // Father constructor called with name: Michael, age: 50, funding: 50000
    // Son constructor called with name: John, age: 20, funding: 1000
}
void test02(){
    Daughter<string, int, float, string, int, float> daughter("Alice", 18, 2000.0, "Sarah", 45, 30000.0);
    fundingcalculate(daughter);

}

int main(){
    test01();
    test02();
    return 0;
}   