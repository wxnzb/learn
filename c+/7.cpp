#include<iostream>
using namespace std;
class Person
{
    public:
    int a;
    int b;
    int S(void);
    void set(int d,int h);
};
int Person::S(void)
{
    return a*b;
}
void Person::set(int d,int h)
{
    a=d;
    b=h;
}
int main()
{
    Person xi;
    Person wu;
    int ss=0;
    xi.a=2;
    xi.b=9;
    ss=xi.a*xi.b;
    cout<<ss<<endl;
    wu.set(4,5);
    ss=wu.S();
    cout<<ss<<endl;
    return 0;
}
