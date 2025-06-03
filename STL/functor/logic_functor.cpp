#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
using namespace std;

void test01(){
    vector<bool> v1;
    v1.push_back(true);
    v1.push_back(false);
    v1.push_back(true);
    v1.push_back(false);
    v1.push_back(true);

    for (vector<bool>::iterator it = v1.begin(); it < v1.end(); it++){
        cout << *it << endl;
    }
    // cout << endl;
	cout << "----------------------------" << endl;
    vector<bool> v2;
    v2.resize(v1.size()); // this line is critical for the tranform() function which requires the size fo the v2 is known.
    //逻辑非  将v容器搬运到v2中，并执行逻辑非运算
    transform(v1.begin(),v1.end(), v2.begin(),logical_not<bool>());

    for (vector<bool>::iterator it = v2.begin(); it < v2.end(); it++){
        cout << *it << endl;
    }

}

int main () {
    test01();
    return 0;
}