#include<iostream>
using namespace std;
//c++中成员变量和成员函数是分开存储的
// class Person
// {
    
// };
// int main()
// {
//     Person p;
//     cout<<"里面啥都没有"<<sizeof(p)<<endl;//控对象占用的内存空间为1,是为了给这个空对向占一个位置
// }
class Person
{
public:
    int a;//非静态成员变量,只有他属于类的对象上
    static int b;
    void func1(){};
    static void func2(){};
};
int Person::b=0;
int main()
{
    Person p;
    cout<<sizeof(p)<<endl;
    return 0;
}
