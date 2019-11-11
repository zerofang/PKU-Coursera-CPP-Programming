#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string.h>
using namespace std;
class Complex {
private:    
    double r,i;
public:    
    void Print() {
        cout << r << "+" << i << "i" << endl;
    }
    Complex(double real = 0.0, double imaginary = 0.0){
        r = real;
        i = imaginary;
    }
    Complex operator=(const char * s){
        i = 0;
        r = 0;
        int len = strlen(s);
        bool flag = false;
        for (int j = len-2; j >= 0; j--) {
            if (s[j]=='+'){
                flag = true;
                continue;
            }
            if(flag){
                r = r * 10 + (s[j] - '0');
            }else{
                i = i * 10 + (s[j] - '0');
            }
        }
        return Complex(r,i);
    }
};
int main() {
    Complex a;
    a = "3+4i"; a.Print();
    a = "5+6i"; a.Print();
    return 0;
}