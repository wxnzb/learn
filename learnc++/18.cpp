#include<iostream>
#include<string>
using namespace std;
//有元
//全局函数作有元
// class Building
// {
//    friend void test(Building* building);
//     public:
//        Building()
//        {
//         this->keting="客厅";
//         this->bedroom="卧室";
//        }
//        string keting;
//     private:
//        string bedroom;
// };
// void test(Building* building)
// {
//     cout<<building->keting<<endl;
//     cout<<building->bedroom<<endl;//不能直接访问，因为它是私有的，要先变成有元才可以
// }
// int main()
// {
//     Building p;
//     test(&p);
//     return 0;
// }
//类作有元
// class Building;
// class goodgay
// {
// public:
//    goodgay();
//    void visit();
// private:
//   Building *building;//为啥要把它放在私有里面，类的公共可以访问私有，好像也可以public
// };
// class Building
// {
//     friend class goodgay;
// public:
//    Building();
//    string keting;
// private:
//    string bedroom;
// };
// //类外成员函数实现方法
// Building::Building()
// {
//    keting="客厅";
//    bedroom="卧室";
// }
// goodgay::goodgay()
// {
//     building=new Building;
// }
// void goodgay::visit()
// {
//      cout<<building->keting<<endl;
//      cout<<building->bedroom<<endl;//不能直接访问，因为它是私有的，要先变成有元才可以
// }
// void test()
// {
//     goodgay gg;
//     gg.visit();
// }
// int main()
// {
//     test();
//     return 0;
// }
//成员函数作有元
class Building;
class goodgay
{
public:
   goodgay();
   void visit();//然他可以访问Building的私有成员
   void visit2();//让他不可以访问Building的私有成员
private:
  Building *building;//为啥要把它放在私有里面，类的公共可以访问私有，好像也可以public
};
class Building
{
    friend void goodgay::visit();//关键所在
public:
   Building();
   string keting;
private:
   string bedroom;
};
//类外成员函数实现方法
Building::Building()
{
   keting="客厅";
   bedroom="卧室";
}
goodgay::goodgay()
{
    building=new Building;
}
void goodgay::visit()
{
     cout<<building->keting<<endl;
     cout<<building->bedroom<<endl;
}
void goodgay::visit2()
{
     cout<<building->keting<<endl;
    // cout<<building->bedroom<<endl;不能访问
}
void test()
{
    goodgay gg;
    gg.visit();
    gg.visit2();
}
int main()
{
    test();
    return 0;
}

