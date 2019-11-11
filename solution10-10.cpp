#include <iostream>
#include <map>
using namespace std;
// 在此处补充你的代码
class A{
    private:
        int num;
    public:
        static int count;
        A(int n = 0){
            num = n;
            count++;
        }
        virtual ~A(){
            cout << "A::destructor" << endl;
        }

        void operator delete(void *A){
            count--;
        }
};

class B : public A{
    public:
    B(int n = 0) : A(n){};
    ~B(){
        cout << "B::destructor" << endl;
    }
};

int A::count = 0;
void func(B b) { }
int main()
{
        A a1(5),a2;
        cout << A::count << endl;
        B b1(4);
        cout << A::count << endl;
        func(b1);
        cout << A::count << endl;
        A * pa = new B(4);
        cout << A::count << endl;
        delete pa;
        cout << A::count << endl;
        return 0;
}