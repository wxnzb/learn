#include<iostream>
#include<cstring>
void Print(struct person a);
void PPrint(struct person* b);
using namespace std;
struct person
{
    char name[20];
    int age;
};
int main()
{
    person wuxi;
    strcpy(wuxi.name,"wuxixi");
    wuxi.age=20;
    Print( wuxi);
    PPrint(&wuxi);                                                                                                                         
    return 0;
}
void Print(struct person a)
{
    cout<<"姓名："<<a.name<<endl;
    cout<<"年龄："<<a.age<<endl;
}
void PPrint(struct person* b)
{
    cout<<"姓名："<<b->name<<endl;
    cout<<"年龄："<<b->age<<endl;
}
