// #include<iostream>
// using namespace std;
// class A
// {
//     public:
//     int a;
//     int b;
//     A add(const A & c)
//     {
//         A tmp;
//         tmp.a=(*this).a+c.a;
//         tmp.b=(*this).b+c.b;
//         return tmp;
//     };
// };
// int main()
// {
//     A w,z;
//     w.a=9;
//     w.b=8;
//     z.a=1;
//     z.b=0;
//     A y=w.add(z);
//     cout<<y.a<<endl;
//     cout<<y.b<<endl;
//     return 0;
// }
//
// #include<iostream>
// using namespace std;
// class A
// {
//     public:
//     int a;
//     int b;
//     public:
//     friend A operator+(const A &q,const A & c);
// };
//  A operator+(const A & q,const A & c)
//     {
//         A tmp;
//         tmp.a=q.a+c.a;
//         tmp.b=q.b+c.b;
//         return tmp;
//     };
// int main()
// {
//     A w,z;
//     w.a=9;
//     w.b=8;
//     z.a=1;
//     z.b=0;
//     A y=w+z;
//     cout<<y.a<<endl;
//     cout<<y.b<<endl;
//     return 0;
// }
#include<iostream>
using namespace std;
class A
{
    public:
    int a;
    int b;
    public:
    A operator+(const A & c)
    {
        A tmp;
        tmp.a=(*this).a+c.a;
        tmp.b=(*this).b+c.b;
        return tmp;
    };
};
int main()
{
    A w,z;
    w.a=9;
    w.b=8;
    z.a=1;
    z.b=0;
    A y=w.operator+(z);
    cout<<y.a<<endl;
    cout<<y.b<<endl;
    return 0;
}



