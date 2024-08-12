#include <iostream>
using namespace std;
// 继承
// 几个都要用到就是公共页面的类
// 针对学科较多的情况
// 继承的好处：减少重复代码
// 语法：class 子类 ：继承方式 FULEI
// 自类 也叫派生类
// fulei 也叫 jilei
//  class Basepage
//  {
//      public:
//      void header()
//      {
//          cout<<"首页，公开课，登陆，注册..."<<endl;
//      }
//      void footor()
//      {
//          cout<<"帮助中心，交流合作，站内地图..."<<endl;
//      }
//      void left()
//      {
//          cout<<"java,python,c++"<<endl;
//      }
//  };
//  //java页面
//  class java:public Basepage{
//  public:
//     void content()
//     {
//      cout<<"java学科视频"<<endl;
//     }
//  };
//  class python:public Basepage{
//  public:
//     void content()
//     {
//      cout<<"python学科视频"<<endl;
//     }
//  };
//  void test()
//  {
//      java ja;
//      ja.header();
//      ja.footor();
//      ja.left();
//      ja.content();
//      python py;
//      py.header();
//      py.footor();
//      py.left();
//      py.content();
//  }
//  int main()
//  {
//      test();
//      return 0;
//  }
// 继承方式//无论什么方式，父亲的私有儿子访问不了
// 公共继承
//  class Base1
//  {
//  public:
//  int a;
//  protected:
//  int b;
//  private:
//  int c;
//  };
//  class Son1:public Base1{
//    public:
//    void func()
//    {
//      a=100;//副中的公共，到子类依然是公共
//      b=20;//副中的保护，到子类依然是保护
//     // c=50;/访问不了
//    }
//  };
//  void test1()
//  {
//      Son1 p;
//      p.a=10;
//      //p.b=20;到Son1中b是保护权限，类外访问不到
//  }
//  //保护继承
//  class Son2:protected Base1{
//    public:
//    void func()
//    {
//      a=100;//副中的公共，到子类是保护
//      b=20;//副中的保护，到子类依然是保护
//     // c=50;/访问不了
//    }
//  };
//  void test2()
//  {
//      Son2 p;
//     // p.a=10;a在父亲是公共，到Son2中a是保护权限，类外访问不到
//      //p.b=20;到Son2中b是保护权限，类外访问不到
//  }
//  //私有继承
//  class Son3:private Base1{
//    public:
//    void func()
//    {
//      a=100;//副中的公共，到子类是私有
//      b=20;//副中的保护，到子类依然是私有
//     // c=50;/访问不了
//    }
//  };
//  void test3()
//  {
//      Son3 p;
//     // p.a=10;//a在父亲是公共,到Son3中a是私有权限,类外访问不到
//      //p.b=20;到Son2中b是私有权限，类外访问不到
//  }
//  class Grandson3:public Son3{
//      public:
//      void func()
//      {
//         // a=100;//访问不到，因为到Son3中a,b都编委私有了，即使孙子变为公共也改变不料
//        //  b=2090;
//      }
//  };
// 继承中的对象模型
// class Base
// {
// public:
//     int a;

// protected:
//     int b;

// private:
//     int c;
// };
// class Son:public Base{
// public:
//    int d;
// };
// int main()
// {
//     Son p;
//     cout<<sizeof(p)<<endl;//是4 12 16中的哪一个呢？16
//     return 0;
//    //fu类中的所有非静态成员属性都会被子类继承辖区。包括私有，他只是被编译器隐藏了，访问不到而一
// }
//继承中构造和xigou的顺序
// class Base
// {
// public:
//   Base()
//   {
//     cout<<"base的构造函数"<<endl;
//   }
//   ~Base()
//   {
//     cout<<"base的xigou函数"<<endl;
//   }
// };
// class Son:public Base{
//     public:
//     Son()
//     {
//         cout<<"son的构造函数"<<endl;
//     }
//     ~Son()
//     {
//         cout<<"son的xigou函数"<<endl;
//     }
// };
// int main()
// {
//     Son p;
//     return 0;
// }
//先构造父亲，在构造孩子，xigou顺序刚好相反
//继承中同名成员
// class Base
// {
// public:
//    Base()
//    {
//     a=100;
//    }
//    void func()
//    {
//     cout<<"base func"<<endl;
//    }
//    void func(int a)
//    {
//     cout<<"base finc int a"<<endl;
//    }
//    int a;
// };
// class Son:public Base{
// public:
//    Son()
//    {
//     a=200;
//    }
//    void func()
//    {
//     cout<<"son func"<<endl;
//    }
//    int a;
// };
// int main()
// {
//     Son p;
//     cout<<p.a<<endl;
//     cout<<p.Base::a<<endl;//若通过子类对象访问到父同名成员。要家作用yu
//     p.func();
//     p.Base::func();
//     //怎样调用父亲的func(int a)呢？p.Base::func(10);可以
//     //但是p.func(100)不幸，若自类出现与父亲同名的成员函数(func)，会将父亲的同名函数隐藏
//     return 0;
// }
//继承中同名静态成员处理方式,和上面基本差不多，就是可以通过类名访问
// class Base
// {
// public:
//    static int a;
//    static void func()
//    {
//     cout<<"base func"<<endl;
//    }
//    static void func(int a)
//    {
//     cout<<"base finc int a"<<endl;
//    }
// };
// int Base::a=10;
// class Son:public Base{
// public:
//    static int a;
//    static void func()
//    {
//     cout<<"son func"<<endl;
//    }
// };
// int Son::a=20;
// int main()
// {
//     Son p;
//     //通过对象访问
//     cout<<p.a<<endl;
//     cout<<p.Base::a<<endl;//若通过子类对象访问到父同名成员。要家作用yu
//     p.func();
//     p.Base::func();
//     //类名访问
//     Son::func();
//     Son::Base::func();
//     //怎样调用父亲的func(int a)呢？p.Base::func(10);可以
//     //但是p.func(100)不幸，若自类出现与父亲同名的成员函数(func)，会将父亲的同名函数隐藏
//     //通过类名访问
//     cout<<Son::a<<endl;
//     cout<<Son::Base::a<<endl;
//     return 0;
// }
//多继承语法
//处理父亲出现同名成员
// class Base1
// {
//     public:
//      Base1()
//      {
//         a=10;
//      }
//      int a;
// };
// class Base2
// {
//     public:
//       Base2()
//       {
//         a=20;
//       }
//       int a;
// };
// class Son:public Base1,public Base2
// {
//     public:
//       Son()
//       {
//         c=30;
//         d=40;
//       }
//       int c;
//       int d;
// };
// int main()
// {
//     Son p1;
//     cout<<p1.Base1::a<<endl;
//     cout<<p1.Base2::a<<endl;
//     return 0;
// }
//🔶继承
//利用心xu继承可以解决
// class animal{
// public:
//    int age;
// };//xu即类
// class sheep:virtual public animal{};
// class tuo:virtual public animal{};//xu继承
// class sheeptuo:public sheep,public tuo{};
// void test()
// {
//     sheeptuo st;
//     st.sheep::age=18;
//     st.tuo::age=28;
//     cout<< st.sheep::age<<endl;
//     cout<<st.tuo::age<<endl;
//     cout<<st.age<<endl;
//    // st.age//该取哪个呢？还有是不是优点浪费资源了，只要一纷纷就可以，但他却继承了两份
// 
