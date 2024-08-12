//初始化列表
#include<iostream>
using namespace std;
class Person{
public:
    //  Person(int a,int b,int c)
    //  {
    //     A=a;
    //     B=b;
    //     C=c;
    //  }
    Person(int a,int b,int c) :A(a),B(b),C(c)
    {

    }
      int A;
      int B;
      int C;
};
void test1()
{
   Person p(1,2,3);//

}
int main()
{
    test1();
    return 0;
}
