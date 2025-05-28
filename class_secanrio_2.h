#include <iostream>
#include <cmath>

using namespace std;
class circle {
    public:
    float position[3] = {0,0,0}; // x, y, z coordinates
    float radius = 1.0; // default radius
};

class point {
    public:
    float position[3] = {0,0,0}; // x, y, z coordinates
};

float distance(const circle &c1, const point &p2) {
    return sqrt(pow(c1.position[0] - p2.position[0], 2) +
                pow(c1.position[1] - p2.position[1], 2) +
                pow(c1.position[2] - p2.position[2], 2));
}
void setcircle(circle &c, float x, float y, float z, float r) {
    c.position[0] = x;
    c.position[1] = y;
    c.position[2] = z;
    c.radius = r;
    cout << "Circle set at (" << x << ", " << y << ", " << z << ") with radius " << r << endl;
}
void setpoint(point &p, float x, float y, float z) {
    p.position[0] = x;
    p.position[1] = y;
    p.position[2] = z;
    cout << "Point set at (" << x << ", " << y << ", " << z << ")" << endl;
}