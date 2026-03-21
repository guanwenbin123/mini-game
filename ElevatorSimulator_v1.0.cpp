#include <iostream>
#include <conio.h>  
#include <windows.h>
using namespace std;

class aa{
    public:
        int a,b,c;
        a=b=c=0;
        void bb(){
            if (_kbhit()){
                if(b<a)
                {
                    for(;b <= a;b++){
                        cout << "电梯所在的楼层:" << b << endl;
                        Sleep(500);
                    }
                    cout << "到了" << endl;
                }
                else
                {
                    for(;b >= a;b--){
                        cout << "电梯所在的楼层:" << b << endl;
                        Sleep(500);
                    }
                    cout << "到了" << endl;
                }
            }    
        }
        void cc(){
            cout << "你现在所在的楼层:" << a << " 请输入你要去的楼层" << endl;
            cin >> a;
            if(b<a)
                {
                    for(;b <= a;b++){
                        cout << "电梯所在的楼层:" << b << endl;
                        Sleep(500);
                    }
                    cout << "到了" << endl;
                }
                else
                {
                    for(;b >= a;b--){
                        cout << "电梯所在的楼层:" << b << endl;
                        Sleep(500);
                    }
                    cout << "到了" << endl;
                }
        }
        void dd(){
            cout << "请输入初始楼层" << endl;
            cin >> a;
                for(;;){
                system("cls");
                cout << "你现在的楼层：" << a << " 按例任意键叫电梯" << endl;
                bb();
                system("cls");
                cc();
            }
        }
};

int main()
{
    aa i;
    i.dd();
    return 0;
}
