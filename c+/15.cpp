#include<iostream>
using namespace std;
// class Person
// {
// public:
//    Person(int age)
//    {
//     age=age;
//    }
//    int age;
// };
// int main()
// {
//     Person p1(10);
//     cout<<p1.age<<endl;//你觉得是10吗？自己可以运行以下
//     return 0;
// }
//解决名称冲突
// class Person
// {
// public:
//    Person(int age)
//    {
//     //this指向被调用成员所属的对象
//     this->age=age;
//    }
//    int age;
// };
// int main()
// {
//     Person p1(10);
//     cout<<p1.age<<endl;//你觉得是10吗？自己可以运行以下
//     return 0;
// }
//返回对象本身用*this
// class Person
// {
// public:
//    Person(int age)
//    {
//     //this指向被调用成员所属的对象
//     this->age=age;
//    }
//    void Personadd(Person& p)
//    {
//     this->age+=p.age;
//    }
//    int age;
// };
// int main()
// {
//     Person p1(10);
//     Person p2(20);
//     p2.Personadd(p1);//但是要家很多次该怎么样呢？
//     cout<<p2.age<<endl;
//     return 0;
// }
class Person
{
public:
   Person(int age)
   {
    //this指向被调用成员所属的对象
    this->age=age;
   }
   Person& Personadd(Person& p)//自己尝试去掉&,他输出的结果又是什么呢？用zhi的方式返回，他会拷贝
 //然后就运行一次这个，也就是20+10,后面的都是拷贝后运行的，与p2本身无关
   {
    this->age+=p.age;
    //this指向p2的指针,*this就是对象本身
    return *this;
   }
   int age;
};
int main()
{
    Person p1(10);
    Person p2(20);
    //链式编成思想
    p2.Personadd(p1).Personadd(p1).Personadd(p1);//20+10+10+10
    cout<<p2.age<<endl;
    return 0;
}

