#include<iostream>
using namespace std;
//运算符重载
//1.+
// class Person
// {
// public:
// //成员函数重载
// // Person operator+(Person& p)
// // {
// //     Person tmp;
// //     tmp.a=this->a+p.a;
// //     tmp.b=this->b+p.b;
// //     return tmp;
// // }
//    int a;
//    int b;
// };
// //全局函数重载
// //本来应该写成Person add(就是自定义的，但是编译器给你规定写成operator+)
// Person operator+(Person& p1,Person& p2)
// {
//     Person tmp;
//     tmp.a=p1.a+p2.a;
//     tmp.b=p1.b+p2.b;
//     return tmp;
// }
// int main()
// {
//     Person p1;
//     p1.a=0;
//     p1.b=1;
//     Person p2;
//     p2.a=3;
//     p2.b=4;
//     Person p3=p1+p2;//重点，不能直接相加，需要实现运算符重载
//     cout<<p3.a<<p3.b<<endl;
//     return 0;
//     //若是成员函数重载，也可写成p1.operator(p2);
//     //若是全局函数重载，也可写成Person p3=operator(p1,p2);
// }
//2.<<
// class Person
// {
// public:
// //利用成员函数重载(不幸)
// //void operator<<(ostream cout){}//p.operator<<(cout)，但是成p<<cout,而我们要cout<<p,所以不行
//    int a;
//    int b;
// };
// //只能利用全局函数
// void operator<<(ostream& cout,Person& p)//本质operator<<(cout,p),即cout<<p
// {
//     //不要忘了是ostream!!&cout,cout也可以写成其他的
//    cout<<"A="<<p.a<<" B="<<p.b;
// }
// int main()
// {
//     Person p;
//     p.a=10;
//     p.b=20;
//     //cout<<p当然不可以
//     cout<<p;//如果你想写<<endl，就要把上面的函数返回值变为cout,类型为ostream
//     return 0;
// }
//3.++
// class Num
// {
//     friend  ostream& operator<<(ostream& out,Num p);
// public:
//    Num()
//    {
//     num=0;
//    }
//    //重载前至++
//    Num& operator++()
//    {
//     num++;
//     return *this;
//    }
//    //重载后至++
//    Num operator++(int)//是为了实现函数重载，他与前面的返回类型无关，int代表占为参数，区分前后至
//     {
//         //县记录当时结果
//         Num tmp=*this;
//         //后递增
//         num++;
//         //最后将记录结果返回
//         return tmp;
//     }
// private:
//    int num;
// };
// ostream& operator<<(ostream& out,Num p)
// {
//     out<<p.num;
//     return out;

// }
// void test()
// {
//     Num p;
//     cout<<++p<<endl;
// }
// void test2()
// {
//     Num p;
//     cout<<p++<<endl;
//     cout<<p<<endl;
// }
// int main()
// {
//     test();
//     test2();
//     return 0;
// }
//4.fuzhi运算符重载
// class Person
// {
// public:
// Person(int age)
// {
//     m_age=new int(age);
// }
// Person& operator=(Person& p)//不要忘了&
// {
//     //编译器提供浅拷贝
//   //  m_age=p.m_age;
//   //应先判断是否属性在对区，若在，影响释放干净
//    if(m_age!=NULL)
//    {
//     delete m_age;
//     m_age=NULL;
//    }
//    m_age=new int(*p.m_age);
//    return *this;
// }
// ~Person()
// {
//    if(m_age!=NULL)
//    {
//     delete m_age;
//     m_age=NULL;
//    }
// }  
//  int* m_age;
// };
// void test()
// {
//     Person p1(18);
//     Person p2(20);
//     p2=p1;//注意：编译器给的是浅拷贝，p2和p1指向同一个对区，不能被释放两次，因此要设计成深拷贝
//     cout<<*p1.m_age<<endl;
//     cout<<*p2.m_age<<endl;
// }
// int main()
// {
//     test();
//     return 0;
// }
//5.关系运算符重载
// class Person
// {
// public:
//    Person(string name,int age)
//    {
//     m_name=name;
//     m_age=age;
//    }
//    //重载==运算符
//    //关键
//    bool operator==(Person &p)
//    {
//     if(this->m_name==p.m_name&&this->m_age==p.m_age)
//     return true;
//     else 
//     return false;
//    }
//     bool operator!=(Person &p)
//    {
//     if(this->m_name!=p.m_name||this->m_age!=p.m_age)
//     return true;
//     else 
//     return false;
//    }
//    string m_name;
//    int m_age;
// };
// void test()
// {
//     Person p1("tom",18);
//     Person p2("tom",18);
//     if(p1==p2)
//     cout<<"p1和p2相同"<<endl;
//     if(p1!=p2)
//     cout<<"p1和p2不相同"<<endl;
// }
// int main()
// {
//     test();
//     return 0;
// }
//6.函数调用运算符重载
class Print
{
public:
   void operator()(string test)
   {
    cout<<test<<endl;
   }
   int operator()(int a,int b)
   {
    return a+b;
   }
};
void test()
{
    Print print;
    print("hello,wuxi");
    cout<<print(1,2)<<endl;
    //匿名函数对象
     cout<<Print()(1,2)<<endl;
}
int main()
{
    test();
    return 0;
}
