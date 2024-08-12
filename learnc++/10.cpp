#include<iostream>
using namespace std;
//构造函数
//分类
//按照参数分类   有参构造 无参构造（也叫默认构造）
//按照类型分类   普通构造 拷贝构造
class Person
{
public:
    Person()//无参构造
    {
        cout<<"Person的构造函数"<<endl;
    }
    Person(int a)//有参构造(有 int a)
    {
        age=a;
        cout<<"Person的构造函数"<<endl;
        //用法：
    }
    ~Person()//xigou函数只能是无参构造，他的作用释放堆对区开放的数据
    {
        cout<<"Person的xi构函数"<<endl;
    }
    int age;
    //拷贝构造函数
    Person(const Person& p)//必须加const，不然就改变了一个定之
    {
        age=p.age;
        cout<<"拷贝构造函数"<<endl;
    }
};
//构造函数的调用
void test()
{
    //括号法
    Person p1;//注意：Person p1();是错误的，编译器会认为它是一个函数生明；
    //匿名对象的特点1：当前行执行后，就立即被系统收回
    //eg:Person(10);cout<<"aaa"<<endl;辉县打印Person的xi构函数，在打因aaa
    Person p2(10);
    //显示法
    Person p3=Person(10);//相当于给匿名函数Person(10)fuzhi,即Person p3(10)
    Person p4=Person(p3);
    //注意：不要用拷贝函数初始化匿名函数
    //eg:Person(p3);
    //yinshi转换法
    Person p5=10;
    Person p6=p5;

}
//拷贝函数使用方法
//1.使用一个以创建完毕的对象来初始化一个新对象
void test1()
{
    Person p1(20);
    Person p2(p1);//现在p2 和 p1里面的数据相等
}
//zhi传递方式给函数参数传zhi
void work(Person p)//拷贝了一份p3传入，里面对p的操作不会影响p3
{
    
}
void test2()
{
    Person p3;
    work(p3);
}
//zhi方式返回局部对象
Person work1()
{
    Person p1;
    return p1;
}
void test3()
{
    Person p4=work1();//拷贝了一份p1副给了p4
}
//默认编译器会提供 1.moren 2.youcan 3.kaobei
//eg:没有
//  Person(const Person& p)//必须加const，不然就改变了一个定之
//     {
//         age=p.age;
//         cout<<"拷贝构造函数"<<endl;
//     }
// void test()
// {
//     Person p1;
//     p1.age=10;
//     Person p2(p1);也是可以运行的
// }
//注意：你写了1,则编译器提供3,不提供2
//你写了3,则编译器不提供1,2；
//深浅拷贝，之前用的都是浅拷贝
class Person
{
public:
    Person()//无参构造
    {
        cout<<"Person的构造函数"<<endl;
    }
    Person(int a,int hh)//有参构造(有 int a)
    {
        age=a;
        height=new int(hh);
        cout<<"Person的构造函数"<<endl;
        //用法：
    }
    ~Person()//xigou函数只能是无参构造，他的作用释放堆对区开放的数据
    {
        if(height!=NULL)
        {
            delete height;
            height=NULL;
        }
        cout<<"Person的xi构函数"<<endl;
    }
    int age;
    int* height;
    //拷贝构造函数
    Person(const Person& p)//必须加const，不然就改变了一个定之
    {
        age=p.age;
        cout<<"拷贝构造函数"<<endl;
        //如果你不写这个，编译器会执行前拷贝，即height=p.height,这样的话两个对象执行一个对区，xigou函数却调用了两次，会出现重新释放对区
        height=new int(*p.height);
    }
};
void test1()
{
    Person p1(10,180);
    Person p2(p1);
}

