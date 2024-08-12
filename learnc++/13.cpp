//静态成员：1,静态成员变量；2,静态成员函数,都说的是共公共
// 1,所有对象共享统一分数据；类内声明，类外初始化；在编译阶段分配内存
// 2,只能访问静态成员变量
#include<iostream>
using namespace std;
class Person
{
public:
    static int a;
    static void func()
    {
        cout<<"hahah"<<endl;
    }
};
int Person::a=10;//记住：不能写成int a=10;
void test()
{
    Person p;
    cout<<p.a<<endl;
    cout<<Person::a<<endl;//不属于某个对象，因此可以用类来表示
    Person p2;
    p2.a=200;
    cout<<p.a<<endl;
}
void test2()
{
    Person p;
    p.func();
    Person::func();
}
int main()
{
    test();
    test2();
    return 0;
}
