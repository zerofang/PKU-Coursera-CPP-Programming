#include <iostream>
using namespace std;
class CType {
    int num;
    public:
    void setvalue(int n){
        num = n;
    }
    int operator++(int){
        int temp = num;
        num = num * num;
        return temp;
    }

    friend ostream& operator << (ostream& o, CType& c){
        o << c.num;
        return o;
    }
};
int main(int argc, char* argv[]) {
    CType obj;
    int n;
    cin>>n;
    while ( n ) {
            obj.setvalue(n);
            cout<<obj++<<" "<<obj<<endl;
            cin>>n;
    }
    return 0;
}