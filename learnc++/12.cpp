//类对象作为类成员
#include<iostream>
#include<string>
using namespace std;
//手机类
class Phone
{
public:
      Phone(string pName)
      {
        cout<<2<<endl;
        m_pName=pName;
      }
      string m_pName;
       ~Phone()//xigou函数只能是无参构造，他的作用释放堆对区开放的数据
    {
        cout<<"Phone的xi构函数"<<endl;
    }

};
//人类
class Person
{
public:
Person(string Name,string pName):name(Name),m_phone(pName)
{
    cout<<1<<endl;
}
     string name;
     Phone m_phone;
      ~Person()//xigou函数只能是无参构造，他的作用释放堆对区开放的数据
    {
        cout<<"Person的xi构函数"<<endl;
    }
};
void test()
{
    Person p("五西","apple");
    cout<<p.name<<"   "<<p.m_phone.m_pName<<endl;
}
int main()
{
    test ();
    return 0;
}
//那各类现有的亚
//县构造对象成员，后构造自身，xigou刚好相反
