#include "class_secanrio_1.h"

bool compare(Cube &a, Cube &b){
    
    float a_a = a.read_a();
    float a_v = a.read_v();

    float b_a = b.read_a();
    float b_v = b.read_v();

    cout << "a's volumn and area " << a_v << " " << a_a << endl;
    cout << "b's volumn and area " << b_v << " " << b_a << endl;

    return (a_v == b_v && a_a == b_a);
}

/*
if you use the compare(const Cube &a, const Cube &b)
the behaviors in the class should be const as well
*/


int main(){
    Cube c1;
    Cube c2;
    c1.setcube(10,20,30);
    c2.setcube(30,20,10);

    c1.getAreaVloumn();
    c2.getAreaVloumn();

    c1.readAreaVolumn();
    c2.readAreaVolumn();

    if (compare(c1,c2)){
        cout << "equal" << endl;
    }
    else{
        cout << "not equal" << endl;
    }

    return EXIT_SUCCESS;
}