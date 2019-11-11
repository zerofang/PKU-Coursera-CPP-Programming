#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>
using namespace std;
// 在此处补充你的代码
class A{
    protected:
        int age;
        char type;
    public:
        A(int a = 0){
            age = a;
            type = 'A';
        }
        int getAge() const{
            return age;
        }
        char getType() const{
            return type;
        }
};
class B : public A{
    public:
    B(int b = 0){
        age = b;
        type = 'B';
    }
};
class Comp{
    public:
    bool operator()(const A* a, const A* b){
        return a->getAge() < b->getAge();
    }
};

void Print(const A* a){
    cout << a->getType() << " " << a->getAge() << endl;
}

int main()
{
    int t;
    cin >> t;
    set<A*,Comp> ct;
    while( t -- ) {
        int n;
        cin >> n;
        ct.clear();
        for( int i = 0;i < n; ++i)	{
                char c; int k;
                cin >> c >> k;

                if( c == 'A')
                        ct.insert(new A(k));
                else
                        ct.insert(new B(k));
        }
        for_each(ct.begin(),ct.end(),Print);
        cout << "****" << endl;
    }
}