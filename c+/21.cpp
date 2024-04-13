#include<iostream>
#include<string>
using namespace std;
//多tai
//满足条件：继承关西，子雷要重写父亲的xu函数
//使用：通过父亲的引用或指针执行类对象
//动物类
//例子
//自治计算机
//普通类
// class calculator
// {
// public:
//   int getresult(string oper)
//   {
//    if(oper=="+")
//    return a1+a2;
//    if(oper=="-")
//    return a1-a2;
//    if(oper=="*")
//    return a1*a2;
//    //如果要家/还要修改原ma
//    return 0;
//   }
//   int a1;
//   int a2;
// };
// //若要扩展新功能，需修改元吗
// //提倡开闭原则，对扩展进行开发，对修改进行关闭
// void test1()
// {
//    calculator p;
//    p.a1=10;
//    p.a2=10;
//    cout<<p.getresult("+")<<endl;
// }
// //利用多台实现
// class abstractcalculator
// {
// public:
//    virtual int getresult()
//    {
//      return 0;
//    }
//    int a1,a2;
// };
// class add:public abstractcalculator
// {
// public:
//   virtual int getresult()
//    {
//       return a1+a2;
//    }
// };
// class sub:public abstractcalculator
// {
// public:
//   virtual int getresult()
//    {
//       return a1-a2;
//    }
// };
// class mul:public abstractcalculator
// {
// public:
//   virtual int getresult()
//    {
//       return a1*a2;
//    }
// };
// void test2()
// {
//    //多台实现，父亲指针或引用自类对象
//    abstractcalculator* abc=new add;
//    abc->a1=10;
//    abc->a2=200;
//    cout<<abc->getresult()<<endl;
//    delete abc;
//    abc=new sub;//虽然释放了，但类型可以不用再说
//    abc->a1=10;
//    abc->a2=200;
//    cout<<abc->getresult()<<endl;
// }
// int main()
// {
//    test1();
//    test2();
//    return 0;
// }
//纯xu函数和抽象类
//一般就是因为你在父亲写的那个函数一般用不上
// class Base
// {
// public:
//    virtual void func()=0;
// };
// //他无法shilihua对象
// void test()
// {
//   // Base p;会报错
//   //new Base;会报错
// }
// //抽象类的子雷必须重写父亲的chunxu函数，否则也属于抽象类
// class son:public Base{
// public://里面啥都不写会成为抽象类，不能是理化
//    void func()
//    {
//       cout<<"func()"<<endl;
//    }
// };
// void test2()
// {
//    son s;
//    s.func();
// }
// int main()
// {
//    test2();
//    return 0;
// }
//案例：制作hede
// class drinking
// {
// public:
//   //主水
//   virtual void boil()=0;
//   //冲泡
//   virtual void brew()=0;
//   //倒入杯中
//   virtual void pour()=0;
//   //加料
//   virtual void add()=0;
//   //制作
//   void drink()
//   {
//    boil();
//    brew();
//    pour();
//    add();
//   }
// };
// //制作coffee
// class coffee:public drinking{
// public:
//    //主水
//   virtual void boil()
//   {
//    cout<<"加矿泉水"<<endl;
//   }
//   //冲泡
//   virtual void brew()
//   {
//    cout<<"冲泡coffee"<<endl;
//   }
//   //倒入杯中
//   virtual void pour()
//   {
//    cout<<"倒入杯中"<<endl;
//   }
//   //加料
//   virtual void add()
//   {
//    cout<<"加牛奶"<<endl;
//   }
// };
// void dowork(drinking* abc)
// {
//    abc->drink();
//    delete abc;//不要忘记释放
// }
// void test1()
// {
//    dowork(new coffee);
// }
// int main()
// {
//    test1();
//    return 0;
// }
//chunxu函数：解决释放子类对区
// class animal
// {
// public:
// animal()
// {
//    cout<<"animal的构造函数"<<endl;
// }
// virtual void speak()=0;
// //  ~animal()//加上virtual
// // {
// //    cout<<"animal的xigou函数"<<endl;
// // }
// //chunxuxigou void ~animal()=0;
//   virtual ~animal()=0;//必须要有一个代码的具体实现，不然如果父亲也有对，就没被释放
// };
// animal:: ~animal()
// {
//    cout<<"animal的chunxuxigou函数"<<endl;
// }
// class cat:public animal{
// public:
//  cat(string name)
//    {
//       cout<<"cat的沟槽函数"<<endl;
//       m_name=new string(name);
//    }
//   void speak()
//   {
//    cout<<*m_name<<"cat在说话"<<endl;
//   }
//   string* m_name;
//   ~cat()
//   {
//     cout<<"cat的xigou函数"<<endl;
//    if(m_name!=NULL)
//    {
//       delete m_name;
//       m_name=NULL;
//    }
//   }
// };
// void test()
// {
//    animal* p=new cat("tom");
//    p->speak();
//    delete p;
// }
// int main()
// {
//    test();
//    return 0;
// }
// //这样运行以下你会发现没有cat的xigou函数,则子雷对区内存美食坊


