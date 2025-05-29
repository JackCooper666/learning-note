/*
案例描述：
设计一个英雄的结构体，包括成员姓名，年龄，性别;创建结构体数组，数组中存放5名英雄。
通过冒泡排序的算法，将数组中的英雄按照年龄进行升序排序，最终打印排序后的结果。
五名英雄信息如下：
		{"刘备",23,"男"},
		{"关羽",22,"男"},
		{"张飞",20,"男"},
		{"赵云",21,"男"},
		{"貂蝉",19,"女"},
*/
#include "structure_secanrio_2.h"
int main(){
    hero heros[5] = {
        {"liubei",23,"male"},
        {"guanyu",22,"male"},
        {"zhangfei",20,"male"},
        {"zhaoyun",21,"male"},
        {"diaochan",19,"female"}
    };

    int len = sizeof(heros)/sizeof(heros[0]);
    bubbleSort(heros,len);
    hero_declare(heros,len);

    return EXIT_SUCCESS;
}
void hero_declare(hero heros[],int len){
    for(int i = 0; i < len; i++){
        cout << "-----------------------" << endl;
        cout << "name: " << heros[i].name << endl;
        cout << "age: " << heros[i].age << endl;
        cout << "gender: " << heros[i].gender << endl;
    }
}
void bubbleSort(hero heros[], int len){
    for(int i=0;i<len -1; i++){
        for(int j = 0; j < len - 1 - i; j++){
            if (heros[j].age > heros[j+1].age)
            {
                hero temp = heros[j];
                heros[j] = heros[j + 1];
                heros[j + 1] = temp;
            }
            
        }
    }

}