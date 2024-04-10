#include<iostream>
using namespace std;
//常函数
class Person
{
    public:
    //本身this是指针常里量，也就是指针的指向是不可以修改的
// eg:
//    void showPerson() 
//    {
//     this==NULL;//不行
//    }
   void showPerson() const//之针指向的zhi变成不可以修改的了 
   {
   //  this->m_A=100会报错
   m_B=100;//不会报错
   }
   void func(){}
   int m_A;
   mutable int m_B;//+了他，在chang函数中也可以修改
 };
//常对象
int main()
{
    const Person p;//常对项
    p.m_A=100;
    p.m_B=200;
    //常对象只能调用常函数
    p.showPerson();//可以
  //  p.func();会报错
    return 0;
}
