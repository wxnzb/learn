#include<iostream>
#include<string>
using  namespace std;
class Person
{
public:
     void shoenumber()
     {
        cout<<"the class has 56 persons"<<endl;
     }
     void Name()
     {
        // if(this==NULL)
        // return;
        cout<<"my name is  "<<name<<endl;//相当是this->name,但现在this==NULL
     }
     string name;
};
int main()
{
    Person *p=NULL;
    p->shoenumber();//没问题
    p->Name();//有问题，this==NULL,加上//就好了，可以提高程序的鲁棒性
}
