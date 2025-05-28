#include "class_secanrio_2.h"

int main(){
    circle c1;
    point p2;
    setcircle(c1, 1.0, 2.0, 3.0, 4.0);
    setpoint(p2, 4.0, 5.0, 6.0);
    float dist = distance(c1, p2);
    cout << "Distance between circle and point: " << dist << endl;
    if (dist <= c1.radius) {
        cout << "Point is inside the circle." << endl;
    } else {
        cout << "Point is outside the circle." << endl;
    }
    return EXIT_SUCCESS;
}