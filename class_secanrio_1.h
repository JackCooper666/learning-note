#include <iostream>
using namespace std;
class Cube{
    public:
    float read_l = length;
    float read_h = heigh;
    float read_w = width;

    float read_a = superficial_area;
    float read_v = volumn;

    void getAreaVloumn(){
        superficial_area 
        = 2*(length * heigh + 
            length * width + 
            heigh * width);
        volumn = length * heigh * width;
    }

    void readAreaVolumn(){
        cout << "superifical area is " << superficial_area << endl;
        cout << "volumn is " << volumn << endl;
    }
    
    void setcube(float l, float h, float w){
        length = l;
        heigh = h;
        width = w;
    }
    private:
    float length;
    float heigh;
    float width;
    float superficial_area;
    float volumn;
};
