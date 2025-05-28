#include <iostream>
#include <string>
using namespace std;

/*
4.4 友元
生活中你的家有客厅(Public)，有你的卧室(Private)

客厅所有来的客人都可以进去，但是你的卧室是私有的，也就是说只有你能进去

但是呢，你也可以允许你的好闺蜜好基友进去。

在程序里，有些私有属性 也想让类外特殊的一些函数或者类进行访问，就需要用到友元的技术

友元的目的就是让一个函数或者类 访问另一个类中私有成员

友元的关键字为 ==friend==

友元的三种实现

全局函数做友元
类做友元
成员函数做友元
*/
class grilfriend; // 前向声明

class myhome {
    // 友元函数
    friend void show(myhome m);
    // 友元类
    friend class goodfrind;
    // 友元成员函数
    friend void grilfriend::visit();

    public:
    myhome(string sittingroom, string bedroom);
    string sittingroom; // 公共属性
    private:
    string bedroom; // 私有属性
};

// define the member function outside the class
myhome::myhome(string sittingroom, string bedroom) {
    this->sittingroom = sittingroom;
    this->bedroom = bedroom;
}


// 友元函数
void show(myhome m) {
    cout << "客厅：" << m.sittingroom << endl;
    cout << "卧室：" << m.bedroom << endl; // 可以访问私有属性
}
void test01() {
    myhome m("客厅", "卧室");
    show(m); // 调用友元函数
}

// 友元类
class goodfrind {
    public:
    goodfrind();
    void visit();
    
    private:
    myhome *m; // 指向myhome类的指针


};
// define the member function outside the class
goodfrind::goodfrind() {
    m = new myhome("客厅", "卧室");
}
void goodfrind::visit() {
    cout << "好基友访问我的家" << endl;
    cout << "客厅：" << m->sittingroom << endl;
    cout << "卧室：" << m->bedroom << endl; // 可以访问私有属性
}

void test02() {

    goodfrind g; // 创建好基友对象
    g.visit(); // 调用访问函数
}

// 友元成员函数
class grilfriend {
    public:
    grilfriend();
    void visit(); // 友元成员函数

    private:
    myhome *m; // 指向myhome类的指针
    
};

grilfriend::grilfriend() {
    m = new myhome("客厅", "卧室");
}
void grilfriend::visit() {
    cout << "好闺蜜访问我的家" << endl;
    cout << "客厅：" << m->sittingroom << endl;
    cout << "卧室：" << m->bedroom << endl; // 可以访问私有属性
}

void test03() {
    grilfriend g; // 创建好闺蜜对象
    g.visit(); // 调用访问函数
}
int main() {
    test03(); 
    return 0;
}