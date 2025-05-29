#include <iostream>
using namespace std;
class Cube{
    public:
    //this part is wrong, because the
    // member variable is not initialized
    //before, the setCube function is called
    // the length, heigh, width, superficial_area and volumn are not initialized
    // float read_l = length;
    // float read_h = heigh;
    // float read_w = width;

    // float read_a = superficial_area;
    // float read_v = volumn;

    // so these should be functions
    float read_l() { return length; }
    float read_h() { return heigh; }
    float read_w() { return width; }
    float read_a() { return superficial_area; }
    float read_v() { return volumn; }

    // for compare(const Cube &a, const Cube &b)
    // float read_l() const { return length; }
    // float read_h() const { return heigh; }
    // float read_w() const { return width; }
    // float read_a() const { return superficial_area; }
    // float read_v() const { return volumn; }


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

    // void readAreaVolume() const {  // Made const since it doesn't modify the object
    //     cout << "superficial area is " << superficial_area << endl;
    //     cout << "volumn is " << volumn << endl;
    // }
    
    void setcube(float l, float h, float w){
        length = l;
        heigh = h;
        width = w;
    }
    
    private:
    float length = 0;
    float heigh = 0;
    float width = 0;
    float superficial_area = 0;
    float volumn = 0;
};
