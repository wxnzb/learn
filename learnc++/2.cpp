#include<iostream>
#include<limits>
using namespace std;
int main()
{
    int x, y;
    int sum = 0;
    cout << "请输入一个数：";
    cin >> x;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除输入缓冲区中的换行符
    cout << "请再输入一个数：";
    cin >> y;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除输入缓冲区中的换行符
    sum = x + y;
    cout << x << "+" << y << "=" << sum << endl;
    cout << "按任意键继续..." << endl;
    cin.get(); // 等待用户输入任意字符
    return 0;
}
//system("pause");适用的是windows
